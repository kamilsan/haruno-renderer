#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "Image.hpp"
#include "Ray.hpp"

#include <memory>

class Camera;

class Renderer
{
public:
  Renderer() = default;

  Image render(std::unique_ptr<Camera> camera, int width, int height) const;
private:
  Color rayTrace(const Ray& ray) const;
};

#endif
