#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "Color.hpp"
#include "Ray.hpp"
#include "Vector3.hpp"

class Light {
 public:
  virtual Color evaluate(const Vector3f& position) const = 0;
  virtual Ray getShadowRay(const Vector3f& position, float& maxT) const = 0;
};

#endif