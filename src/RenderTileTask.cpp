#include "RenderTileTask.hpp"

#include "Camera.hpp"
#include "Integrator.hpp"
#include "ThreadPool.hpp"
#include "Vector3.hpp"

RenderTileTask::RenderTileTask(const RenderParameters& parameters,
                               std::shared_ptr<Integrator> integrator, ImageTile tile,
                               const Camera& camera, const Scene& scene, RNG rng)
    : parameters_(parameters),
      integrator_(integrator),
      tile_(std::move(tile)),
      camera_(camera),
      scene_(scene),
      rng_(std::move(rng)) {
  aspectRatio_ = static_cast<float>(parameters.width) / parameters.height;
}

void RenderTileTask::renderTile() {
  for (unsigned int tileY = 0; tileY < tile_.getHeight(); ++tileY) {
    for (unsigned int tileX = 0; tileX < tile_.getWidth(); ++tileX) {
      const unsigned int x = tile_.getMinX() + tileX;
      const unsigned int y = tile_.getMinY() + tileY;

      Color color{};
      for (unsigned int i = 0; i < parameters_.mcSamples; ++i) {
        const float ndcX =
            aspectRatio_ * (2.0f * ((x + rng_.get()) / (parameters_.width - 1.0f)) - 1.0f);
        const float ndcY = -2.0f * ((y + rng_.get()) / (parameters_.height - 1.0f)) + 1.0f;

        const Ray primaryRay = camera_.getCameraRay(ndcX, ndcY, rng_);
        color += integrator_->integrate(primaryRay, scene_, rng_);
      }

      color /= parameters_.mcSamples;

      tile_.setPixel(tileX, tileY, color);
    }
  }
}
