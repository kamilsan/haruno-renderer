#include "PinholeCamera.hpp"

#include "Math.hpp"

PinholeCamera::PinholeCamera(float fov, const Vector& position, const Vector& forward, const Vector& up): position_(position)
{
  tanHalfFov_ = std::tan(toRadians(fov) * 0.5f);
  forward_ = forward.normalized();
  right_ = up.cross(forward_).normalized();
  up_ = forward_.cross(right_).normalized();
}

Ray PinholeCamera::getCameraRay(float ndcX, float ndcY) const
{
  const float x = ndcX * tanHalfFov_;
  const float y = ndcY * tanHalfFov_;

  const Vector direction{x * right_.x + y * up_.x + forward_.x,
                         x * right_.y + y * up_.y + forward_.y,
                         x * right_.z + y * up_.z + forward_.z};
  
  return Ray(position_, direction.normalized());
}