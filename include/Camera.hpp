#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Ray.hpp"

class Camera
{
public:
  virtual Ray getCameraRay(float ndcX, float ndxY) const = 0;
};

#endif