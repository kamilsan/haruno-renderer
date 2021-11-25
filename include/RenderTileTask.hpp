#ifndef RENDER_TILE_TASK
#define RENDER_TILE_TASK

#include <memory>

#include "ImageTile.hpp"
#include "RNG.hpp"
#include "RenderParameters.hpp"
#include "ThreadPool.hpp"

class Ray;
class Camera;
class Scene;
class Integrator;

class RenderTileTask : public Task<ImageTile> {
 public:
  RenderTileTask(const RenderParameters& parameters, std::shared_ptr<Integrator> integrator,
                 ImageTile tile, const Camera& camera, const Scene& scene, RNG rng);

  ImageTile run() override {
    renderTile();
    return tile_;
  }

 private:
  void renderTile();

  RenderParameters parameters_;
  std::shared_ptr<Integrator> integrator_;
  float aspectRatio_;
  ImageTile tile_;
  const Camera& camera_;
  const Scene& scene_;
  mutable RNG rng_;
};

#endif