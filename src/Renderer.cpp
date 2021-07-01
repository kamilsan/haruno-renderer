#include "Renderer.hpp"
#include "Vector.hpp"
#include "Ray.hpp"
#include "Camera.hpp"
#include "Material.hpp"
#include "Scene.hpp"
#include "Object.hpp"
#include "Environment.hpp"
#include "Light.hpp"
#include "BRDF.hpp"
#include "Math.hpp"
#include "ThreadPool.hpp"
#include "RenderTileTask.hpp"

#include <iostream>
#include <functional>

Renderer::Renderer(unsigned int width, unsigned int height, unsigned int numTiles, 
  unsigned int threads, unsigned int samples): 
  width_(width), height_(height), numTiles_(numTiles), threads_(threads), samples_(samples), rng_() {}

Image Renderer::render(std::unique_ptr<Camera> camera, const Scene& scene) const
{
  Image result{width_, height_};

  const unsigned int numTilesX = std::sqrt(numTiles_);
  const unsigned int numTilesY = std::ceil(static_cast<float>(numTiles_) / numTilesX);
  const unsigned int tileSizeX = std::ceil(static_cast<float>(width_) / numTilesX);
  const unsigned int tileSizeY = std::ceil(static_cast<float>(height_) / numTilesY);

  ThreadPool<ImageTile> pool{threads_};
  std::vector<std::future<ImageTile>> results{};
  results.reserve(numTiles_);

  for(unsigned int tileY = 0; tileY < numTilesY; ++tileY)
  {
    for(unsigned int tileX = 0; tileX < numTilesX; ++tileX)
    {
      const unsigned int tileId = tileY * numTilesY + tileX;
      const unsigned int tileMinX = tileX * tileSizeX;
      const unsigned int tileMinY = tileY * tileSizeY;
      unsigned int tileMaxX = (tileX + 1) * tileSizeX;
      unsigned int tileMaxY = (tileY + 1) * tileSizeY;

      if(tileMaxX > width_ - 1)
      {
        tileMaxX = width_ - 1;
      }
      if(tileMaxY > height_ - 1)
      {
        tileMaxY = height_ - 1;
      }

      ImageTile tile{tileMinX, tileMaxX, tileMinY, tileMaxY};
      auto result = 
        pool.addTask(std::make_unique<RenderTileTask>(width_, height_, samples_, std::move(tile), *camera, scene, rng_.createChild(tileId)));
      results.emplace_back(std::move(result));
    }
  }

  for(size_t i = 0; i < results.size(); ++i)
  {
    const auto tile = results[i].get();
    for(unsigned int tileY = 0; tileY < tile.getHeight(); ++tileY)
    {
      for(unsigned int tileX = 0; tileX < tile.getWidth(); ++tileX)
      {
        const auto imageX = tileX + tile.getMinX();
        const auto imageY = tileY + tile.getMinY();

        const auto color = tile.getPixel(tileX, tileY);
        result.setPixel(imageX, imageY, color);
      }
    }

    std::cout << "Rendering... " << 100.f * i / (results.size() - 1.0f) << "%\n";
  }

  return result;
}