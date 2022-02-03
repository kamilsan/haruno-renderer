#ifndef INTEGRATOR_HPP
#define INTEGRATOR_HPP

class Ray;
class Camera;
class Scene;
class RNG;
class SurfaceInfo;
class Material;

#include "Color.hpp"
#include "Vector3.hpp"

class Integrator {
 public:
  virtual Color integrate(const Ray& ray, const Scene& scene, RNG& rng) const = 0;

 protected:
  virtual Color computeDirectLighting(const Scene& scene, const Vector3f& position,
                                      const Vector3f& wo, const SurfaceInfo& surfaceInfo,
                                      const Material& material, RNG& rng) const;

 private:
};

#endif  // INTEGRATOR_HPP