#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include "Vector3.hpp"

class Color;
class Ray;

class Environment {
 public:
  virtual Color getColor(const Vector3f& direction, float maxT = -1) const = 0;
  virtual Color getTransmittance(const Ray& ray, float maxT) const = 0;
};

#endif
