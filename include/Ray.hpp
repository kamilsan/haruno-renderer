#ifndef RAY_HPP
#define RAY_HPP

#include "Vector3.hpp"

class Ray {
 public:
  Ray(const Vector3f& origin, const Vector3f& direction) : origin_(origin), direction_(direction) {}

  Vector3f at(float t) const { return origin_ + t * direction_; }
  Vector3f operator()(float t) const { return origin_ + t * direction_; }

  Vector3f getOrigin() const { return origin_; }
  Vector3f getDirection() const { return direction_; }

 private:
  Vector3f origin_;
  Vector3f direction_;
};

#endif
