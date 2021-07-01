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
  RenderTileTask(int width, int height, unsigned int samples, ImageTile tile, 
    const Camera& camera, const Scene& scene, RNG rng);

  ImageTile run() override
  { 
    renderTile();
    return tile_; 
  }

private:
  void renderTile();
  Color rayTrace(const Ray& camera_ray) const;

  int width_;
  int height_;
  float aspectRatio_;
  unsigned int samples_;
  ImageTile tile_;
  const Camera& camera_;
  const Scene& scene_;
  mutable RNG rng_;
};

#endif