#ifndef RAY_HPP
#define RAY_HPP

#include "Types.hpp"

class Ray {
 public:
  Ray(const Vector3t& origin, const Vector3t& direction) : origin_(origin), direction_(direction) {}

  Vector3t at(Float t) const { return origin_ + t * direction_; }
  Vector3t operator()(Float t) const { return origin_ + t * direction_; }

  Vector3t getOrigin() const { return origin_; }
  Vector3t getDirection() const { return direction_; }

 private:
  Vector3t origin_;
  Vector3t direction_;
};

#endif
