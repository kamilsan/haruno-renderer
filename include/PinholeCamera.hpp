#ifndef PINHOLE_CAMERA_HPP
#define PINHOLE_CAMERA_HPP

#include "Camera.hpp"

// TODO
class PinholeCamera : public Camera
{
public:
  PinholeCamera() = default;

  inline Ray getCameraRay(float ndcX, float ndcY) const;
private:
};

Ray PinholeCamera::getCameraRay(float ndcX, float ndcY) const
{
  const Vector origin{0, 0, -1.0f};
  const Vector direction = Vector{ndcX, ndcY, 1}.normalized();

  return Ray{origin, direction};
}

#endif