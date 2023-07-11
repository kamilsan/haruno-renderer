#ifndef AMBIENT_OCCLUSION_HPP
#define AMBIENT_OCCLUSION_HPP

#include "Integrator.hpp"

class AmbientOcclusion : public Integrator {
 public:
  AmbientOcclusion(Float radius) : radius_(radius) {}

  Color integrate(const Ray& ray, const Scene& scene, RNG& rng) const;

 private:
  Float radius_ = 1.0;
};

#endif