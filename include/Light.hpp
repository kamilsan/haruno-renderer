#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "Color.hpp"
#include "Ray.hpp"
#include "Vector3.hpp"

class RNG;
struct SurfaceInfo;

class Light {
 public:
  virtual Color evaluate(const Vector3f& position) const = 0;
  virtual Ray getShadowRay(const Vector3f& position, float& maxT) const = 0;
  virtual bool isDelta() const = 0;
  virtual float pdf() const = 0;
  virtual Color sampleLe(Vector3f& position, RNG& rng) const = 0;
  virtual float intersects(const Ray& ray, SurfaceInfo& surfaceInfo) const = 0;
};

#endif