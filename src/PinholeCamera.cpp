#include "PinholeCamera.hpp"

#include "Math.hpp"

PinholeCamera::PinholeCamera(Float fov, const Vector3t& position, const Vector3t& forward,
                             const Vector3t& up)
    : position_(position) {
  tanHalfFov_ = std::tan(toRadians(fov) * 0.5);
  forward_ = forward.normalized();
  right_ = up.cross(forward_).normalized();
  up_ = forward_.cross(right_).normalized();
}

Ray PinholeCamera::getCameraRay(Float ndcX, Float ndcY, RNG&) const {
  const Float x = ndcX * tanHalfFov_;
  const Float y = ndcY * tanHalfFov_;

  const Vector3t direction{x * right_.x + y * up_.x + forward_.x,
                           x * right_.y + y * up_.y + forward_.y,
                           x * right_.z + y * up_.z + forward_.z};

  return Ray(position_, direction.normalized());
}