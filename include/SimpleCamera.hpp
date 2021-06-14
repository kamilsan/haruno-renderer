#ifndef SIMPLE_CAMERA_HPP
#define SIMPLE_CAMERA_HPP

#include "Camera.hpp"
#include "Vector.hpp"

class SimpleCamera : public Camera
{
public:
  SimpleCamera(float fov, float lensRadius, float focalLength, const Vector& position, const Vector& forward, const Vector& up);
  SimpleCamera(float fov, float lensRadius, float focalLength, const Vector& position):
    SimpleCamera(fov, lensRadius, focalLength, position, Vector{0, 0, 1}, Vector{0, 1, 0}) {}

  const Vector& getPosition() const { return position_; }
  const Vector& getForward() const { return forward_; }
  const Vector& getUp() const { return up_; }

  Ray getCameraRay(float ndcX, float ndcY, RNG& rng) const override;
private:
  float tanHalfFov_;
  float lensRadius_;
  float focalLength_;
  Vector position_;
  Vector forward_;
  Vector right_;
  Vector up_;
};

#endif