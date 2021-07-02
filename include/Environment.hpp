#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

class Color;
class Vector;

class Environment {
 public:
  virtual Color getColor(const Vector& direction) const = 0;
};

#endif
