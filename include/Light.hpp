#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "Color.hpp"
#include "Ray.hpp"

class Vector;

class Light {
 public:
  virtual Color evaluate(const Vector& position) const = 0;
  virtual Ray getShadowRay(const Vector& position, float& maxT) const = 0;
};

#endif