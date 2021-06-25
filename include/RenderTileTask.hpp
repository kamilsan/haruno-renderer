#ifndef RENDER_TILE_TASK
#define RENDER_TILE_TASK

#include "ThreadPool.hpp"
#include "ImageTile.hpp"
#include "RNG.hpp"

class Ray;
class Camera;
class Scene;

class RenderTileTask : public Task<ImageTile>
{
public:
  RenderTileTask(int width, int height, unsigned int samples, unsigned int depth, 
    ImageTile tile, const Camera& camera, const Scene& scene, RNG rng);

  ImageTile run() override
  { 
    renderTile(tile_, camera_, scene_, rng_);
    return tile_; 
  }

private:
  void renderTile(ImageTile& tile, const Camera& camera, const Scene& scene, RNG rng) const;
  Color rayTrace(const Ray& ray, const Scene& scene, int depth, RNG& rng) const;

  int width_;
  int height_;
  float aspectRatio_;
  unsigned int samples_;
  unsigned int depth_;
  ImageTile tile_;
  const Camera& camera_;
  const Scene& scene_;
  mutable RNG rng_;
};

#endif