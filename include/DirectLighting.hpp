#ifndef DIRECT_LIGHTING_HPP
#define DIRECT_LIGHTING_HPP

#include <cstddef>

#include "Integrator.hpp"

class DirectLighting : public Integrator {
 public:
  DirectLighting(size_t maxDepth) : maxDepth_(maxDepth) {}

  Color integrate(const Ray& cameraRay, const Scene& scene, RNG& rng) const override;

 private:
  size_t maxDepth_;
};

#endif  // DIRECT_LIGHTING_HPP