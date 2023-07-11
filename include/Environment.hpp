#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include "Vector3.hpp"

class Color;

class Environment {
 public:
  virtual Color getColor(const Vector3t& direction) const = 0;
};

#endif
