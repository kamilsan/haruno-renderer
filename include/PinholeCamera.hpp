#ifndef PINHOLE_CAMERA_HPP
#define PINHOLE_CAMERA_HPP

#include "Camera.hpp"
#include "Vector.hpp"

class PinholeCamera : public Camera
{
public:
  PinholeCamera(float fov, const Vector& position, const Vector& forward, const Vector& up);
  PinholeCamera(float fov, const Vector& position):
    PinholeCamera(fov, position, Vector{0, 0, 1}, Vector{0, 1, 0}) {}

  const Vector& getPosition() const { return position_; }
  const Vector& getForward() const { return forward_; }
  const Vector& getUp() const { return up_; }

  Ray getCameraRay(float ndcX, float ndcY) const override;
private:
  float tanHalfFov_;
  Vector position_;
  Vector forward_;
  Vector right_;
  Vector up_;
};

#endif