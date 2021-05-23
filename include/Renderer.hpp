#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <memory>

#include "Image.hpp"
#include "RNG.hpp"

class Ray;
class Camera;
class Scene;

class Renderer
{
public:
  Renderer(int width, int height, unsigned int samples, unsigned int depth): 
    width_(width), height_(height), samples_(samples), depth_(depth), rng_() {}

  Image render(std::unique_ptr<Camera> camera, const Scene& scene) const;
private:
  Color rayTrace(const Ray& ray, const Scene& scene, int depth) const;

  int width_;
  int height_;
  unsigned int samples_;
  unsigned int depth_;
  mutable RNG rng_;
};

#endif
