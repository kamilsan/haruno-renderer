#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <memory>

#include "Image.hpp"
#include "ImageTile.hpp"
#include "RNG.hpp"
#include "RenderParameters.hpp"

class Ray;
class Camera;
class Scene;

class Renderer {
 public:
  Renderer(const RenderParameters& parameters);

  Image render(std::unique_ptr<Camera> camera, const Scene& scene) const;

 private:
  RenderParameters parameters_;
  mutable RNG rng_;
};

#endif
