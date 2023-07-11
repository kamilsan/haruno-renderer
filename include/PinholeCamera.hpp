#ifndef PINHOLE_CAMERA_HPP
#define PINHOLE_CAMERA_HPP

#include "Camera.hpp"
#include "Vector3.hpp"

class PinholeCamera : public Camera {
 public:
  PinholeCamera(Float fov, const Vector3t& position, const Vector3t& forward, const Vector3t& up);
  PinholeCamera(Float fov, const Vector3t& position)
      : PinholeCamera(fov, position, Vector3t{0, 0, 1}, Vector3t{0, 1, 0}) {}

  const Vector3t& getPosition() const { return position_; }
  const Vector3t& getForward() const { return forward_; }
  const Vector3t& getUp() const { return up_; }

  Ray getCameraRay(Float ndcX, Float ndcY, RNG&) const override;

 private:
  Float tanHalfFov_;
  Vector3t position_;
  Vector3t forward_;
  Vector3t right_;
  Vector3t up_;
};

#endif