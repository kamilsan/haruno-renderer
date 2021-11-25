#ifndef INTEGRATOR_HPP
#define INTEGRATOR_HPP

class Ray;
class Camera;
class Scene;
class RNG;

#include "Color.hpp"

class Integrator {
 public:
  virtual Color integrate(const Ray& ray, const Scene& scene, RNG& rng) = 0;

 private:
};

#endif  // INTEGRATOR_HPP