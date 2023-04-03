#include "Renderer.hpp"

#include <functional>
#include <iostream>

#include "BRDF.hpp"
#include "Camera.hpp"
#include "Environment.hpp"
#include "Integrator.hpp"
#include "Light.hpp"
#include "Material.hpp"
#include "Math.hpp"
#include "Object.hpp"
#include "Ray.hpp"
#include "RenderTileTask.hpp"
#include "Scene.hpp"
#include "ThreadPool.hpp"

Renderer::Renderer(const RenderParameters& parameters, std::shared_ptr<Integrator> integrator,
                   std::unique_ptr<ToneMapper> toneMapper)
    : parameters_(parameters), integrator_(integrator), toneMapper_(std::move(toneMapper)), rng_() {
  if (parameters.seed.has_value()) {
    rng_ = RNG(parameters.seed.value());
  }
}

Renderer::Renderer(const RenderParameters& parameters, std::shared_ptr<Integrator> integrator)
    : Renderer(parameters, integrator, nullptr) {}

Image Renderer::render(std::unique_ptr<Camera> camera, const Scene& scene) const {
  Image result{parameters_.width, parameters_.height};

  const unsigned int numTilesX = std::sqrt(parameters_.numTiles);
  const unsigned int numTilesY = std::ceil(static_cast<float>(parameters_.numTiles) / numTilesX);
  const auto finalTilesCount = numTilesX * numTilesY;

  const unsigned int tileSizeX = std::ceil(static_cast<float>(parameters_.width) / numTilesX);
  const unsigned int tileSizeY = std::ceil(static_cast<float>(parameters_.height) / numTilesY);

  std::vector<std::pair<unsigned int, ImageTile>> tiles;
  tiles.reserve(finalTilesCount);

  for (unsigned int tileY = 0; tileY < numTilesY; ++tileY) {
    for (unsigned int tileX = 0; tileX < numTilesX; ++tileX) {
      const unsigned int tileId = tileY * numTilesY + tileX;

      const unsigned int tileMinX = tileX * tileSizeX;
      const unsigned int tileMinY = tileY * tileSizeY;

      unsigned int tileMaxX = (tileX + 1) * tileSizeX;
      unsigned int tileMaxY = (tileY + 1) * tileSizeY;

      if (tileMaxX > parameters_.width - 1) {
        tileMaxX = parameters_.width - 1;
      }
      if (tileMaxY > parameters_.height - 1) {
        tileMaxY = parameters_.height - 1;
      }

      ImageTile tile{tileMinX, tileMaxX, tileMinY, tileMaxY};
      tiles.emplace_back(std::make_pair(tileId, tile));
    }
  }

  const auto tileDistToCenter = [&](const ImageTile& tile) {
    const auto imageCenterX = parameters_.width * 0.5f;
    const auto imageCenterY = parameters_.height * 0.5f;

    const auto tileCenterX = (tile.getMinX() + tile.getMaxX()) * 0.5f;
    const auto tileCenterY = (tile.getMinY() + tile.getMaxY()) * 0.5f;

    const auto dx = tileCenterX - imageCenterX;
    const auto dy = tileCenterY - imageCenterY;

    return dx * dx + dy * dy;
  };

  std::sort(tiles.begin(), tiles.end(), [&](const auto& tile1, const auto& tile2) {
    return tileDistToCenter(tile1.second) < tileDistToCenter(tile2.second);
  });

  ThreadPool<ImageTile> pool{parameters_.threads};
  std::vector<std::future<ImageTile>> results{};
  results.reserve(finalTilesCount);

  for (const auto& tileWithId : tiles) {
      const auto& [tileId, tile] = tileWithId;
      auto result = pool.addTask(std::make_unique<RenderTileTask>(
          parameters_, integrator_, std::move(tile), *camera, scene, rng_.createChild(tileId)));
      results.emplace_back(std::move(result));
  }

  for (size_t i = 0; i < results.size(); ++i) {
    const auto tile = results[i].get();
    for (unsigned int tileY = 0; tileY < tile.getHeight(); ++tileY) {
      for (unsigned int tileX = 0; tileX < tile.getWidth(); ++tileX) {
        const auto imageX = tileX + tile.getMinX();
        const auto imageY = tileY + tile.getMinY();

        const auto color = tile.getPixel(tileX, tileY);
        result.setPixel(imageX, imageY, color);
      }
    }

    if (parameters_.saveIntermediate) {
      if (i % parameters_.saveFrequency == 0) {
        // TODO: use some callback to delegate image saving to someone else
        if (toneMapper_) {
          const auto resultMapped = toneMapper_->apply(result);
          resultMapped.save("render_" + std::to_string(i) + ".png");
        } else {
          result.save("render_" + std::to_string(i) + ".png");
        }
      }
    }

    std::cout << "Rendering... " << 100.f * i / (results.size() - 1.0f) << "%\n";
  }

  if (toneMapper_) {
    return toneMapper_->apply(result);
  }

  return result;
}