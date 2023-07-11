#include "SimpleCamera.hpp"

#include "Math.hpp"
#include "RNG.hpp"

SimpleCamera::SimpleCamera(Float fov, Float lensRadius, Float focalLength, const Vector3t& position,
                           const Vector3t& forward, const Vector3t& up)
    : lensRadius_(lensRadius), focalLength_(focalLength), position_(position) {
  tanHalfFov_ = std::tan(toRadians(fov) * 0.5);
  forward_ = forward.normalized();
  right_ = up.cross(forward_).normalized();
  up_ = forward_.cross(right_).normalized();
}

Ray SimpleCamera::getCameraRay(Float ndcX, Float ndcY, RNG& rng) const {
  const Float x = ndcX * tanHalfFov_;
  const Float y = ndcY * tanHalfFov_;

  const Vector3t lensSample = lensRadius_ * rng.sampleCircle();
  const Vector3t onFocalPlane = Vector3t{focalLength_ * x, focalLength_ * y, focalLength_};
  const Vector3t direction = onFocalPlane - lensSample;

  const Vector3t transformed{
      direction.x * right_.x + direction.y * up_.x + direction.z * forward_.x,
      direction.x * right_.y + direction.y * up_.y + direction.z * forward_.y,
      direction.x * right_.z + direction.y * up_.z + direction.z * forward_.z};

  const Vector3t origin = position_ + Vector3t{lensSample.x * right_.x + lensSample.y * up_.x,
                                               lensSample.x * right_.y + lensSample.y * up_.y, 0};

  return Ray(origin, transformed.normalized());
}