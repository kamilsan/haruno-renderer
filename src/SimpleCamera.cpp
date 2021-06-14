#include "SimpleCamera.hpp"

#include "Math.hpp"
#include "RNG.hpp"

SimpleCamera::SimpleCamera(float fov, float lensRadius, float focalLength, const Vector& position, const Vector& forward, const Vector& up): 
  lensRadius_(lensRadius), focalLength_(focalLength), position_(position)
{
  tanHalfFov_ = std::tan(toRadians(fov) * 0.5f);
  forward_ = forward.normalized();
  right_ = up.cross(forward_).normalized();
  up_ = forward_.cross(right_).normalized();
}

Ray SimpleCamera::getCameraRay(float ndcX, float ndcY, RNG& rng) const
{
  const float x = ndcX * tanHalfFov_;
  const float y = ndcY * tanHalfFov_;

  const Vector lensSample = lensRadius_ * rng.sampleCircle();
  const Vector onFocalPlane = Vector{focalLength_ * x, focalLength_ * y, focalLength_};
  const Vector direction = onFocalPlane - lensSample;

  const Vector transformed{direction.x * right_.x + direction.y * up_.x + direction.z * forward_.x,
                           direction.x * right_.y + direction.y * up_.y + direction.z * forward_.y,
                           direction.x * right_.z + direction.y * up_.z + direction.z * forward_.z};

  const Vector origin = position_ + Vector{lensSample.x * right_.x + lensSample.y * up_.x,
                                           lensSample.x * right_.y + lensSample.y * up_.y,
                                           0}; 
  
  return Ray(origin, transformed.normalized());
}