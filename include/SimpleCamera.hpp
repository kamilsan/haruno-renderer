#ifndef SIMPLE_CAMERA_HPP
#define SIMPLE_CAMERA_HPP

#include "Camera.hpp"
#include "Vector3.hpp"

class SimpleCamera : public Camera {
 public:
  SimpleCamera(float fov, float lensRadius, float focalLength, const Vector3f& position,
               const Vector3f& forward, const Vector3f& up);
  SimpleCamera(float fov, float lensRadius, float focalLength, const Vector3f& position)
      : SimpleCamera(fov, lensRadius, focalLength, position, Vector3f{0, 0, 1}, Vector3f{0, 1, 0}) {
  }

  const Vector3f& getPosition() const { return position_; }
  const Vector3f& getForward() const { return forward_; }
  const Vector3f& getUp() const { return up_; }

  Ray getCameraRay(float ndcX, float ndcY, RNG& rng) const override;

 private:
  float tanHalfFov_;
  float lensRadius_;
  float focalLength_;
  Vector3f position_;
  Vector3f forward_;
  Vector3f right_;
  Vector3f up_;
};

#endif