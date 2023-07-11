#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <memory>

#include "Color.hpp"
#include "Ray.hpp"
#include "Vector3.hpp"

class RNG;
class Object;
struct SurfaceInfo;

class Light {
 public:
  virtual std::shared_ptr<Object> getObject() { return nullptr; }

  virtual Color evaluate(const Vector3t& position) const = 0;
  virtual Ray getShadowRay(const Vector3t& position, Float& maxT) const = 0;
  virtual bool isDelta() const = 0;
  virtual Color sampleLe(Vector3t& position, SurfaceInfo& surfaceInfo, RNG& rng,
                         Float& pdf) const = 0;
};

#endif