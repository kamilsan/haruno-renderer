#ifndef RAY_HPP
#define RAY_HPP

#include "Vector.hpp"

class Ray
{
public:
  Ray(const Vector& origin, const Vector& direction): origin_(origin), direction_(direction) {}

  Vector at(float t) const { return origin_ + t * direction_; }
  Vector operator()(float t) const { return origin_ + t * direction_; }

  Vector getOrigin() const { return origin_; }
  Vector getDirection() const { return direction_; }

private:
  Vector origin_;
  Vector direction_;
};

#endif
