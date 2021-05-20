#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <memory>

#include "Image.hpp"

class Ray;
class Camera;
class Scene;

class Renderer
{
public:
  Renderer(int width, int height): width_(width), height_(height) {}

  Image render(std::unique_ptr<Camera> camera, const Scene& scene) const;
private:
  Color rayTrace(const Ray& ray, const Scene& scene) const;

  int width_;
  int height_;
};

#endif
