#ifndef SIMPLE_CAMERA_HPP
#define SIMPLE_CAMERA_HPP

#include "Camera.hpp"
#include "Vector3.hpp"

class SimpleCamera : public Camera {
 public:
  SimpleCamera(Float fov, Float lensRadius, Float focalLength, const Vector3t& position,
               const Vector3t& forward, const Vector3t& up);
  SimpleCamera(Float fov, Float lensRadius, Float focalLength, const Vector3t& position)
      : SimpleCamera(fov, lensRadius, focalLength, position, Vector3t{0, 0, 1}, Vector3t{0, 1, 0}) {
  }

  const Vector3t& getPosition() const { return position_; }
  const Vector3t& getForward() const { return forward_; }
  const Vector3t& getUp() const { return up_; }

  Ray getCameraRay(Float ndcX, Float ndcY, RNG& rng) const override;

 private:
  Float tanHalfFov_;
  Float lensRadius_;
  Float focalLength_;
  Vector3t position_;
  Vector3t forward_;
  Vector3t right_;
  Vector3t up_;
};

#endif