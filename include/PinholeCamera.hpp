#ifndef PINHOLE_CAMERA_HPP
#define PINHOLE_CAMERA_HPP

#include "Camera.hpp"
#include "Vector3.hpp"

class PinholeCamera : public Camera {
 public:
  PinholeCamera(float fov, const Vector3f& position, const Vector3f& forward, const Vector3f& up);
  PinholeCamera(float fov, const Vector3f& position)
      : PinholeCamera(fov, position, Vector3f{0, 0, 1}, Vector3f{0, 1, 0}) {}

  const Vector3f& getPosition() const { return position_; }
  const Vector3f& getForward() const { return forward_; }
  const Vector3f& getUp() const { return up_; }

  Ray getCameraRay(float ndcX, float ndcY, RNG&) const override;

 private:
  float tanHalfFov_;
  Vector3f position_;
  Vector3f forward_;
  Vector3f right_;
  Vector3f up_;
};

#endif