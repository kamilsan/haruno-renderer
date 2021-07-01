#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <memory>

#include "Image.hpp"
#include "ImageTile.hpp"
#include "RNG.hpp"

class Ray;
class Camera;
class Scene;

class Renderer
{
public:
  Renderer(unsigned int width, unsigned int height, unsigned int numTiles, unsigned int threads, unsigned int samples);

  Image render(std::unique_ptr<Camera> camera, const Scene& scene) const;
private:
  unsigned int width_;
  unsigned int height_;
  unsigned int numTiles_;
  unsigned int threads_;
  unsigned int samples_;
  mutable RNG rng_;
};

#endif
