#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Ray.hpp"

class RNG;

class Camera {
 public:
  virtual ~Camera() = default;
  virtual Ray getCameraRay(Float ndcX, Float ndxY, RNG& rng) const = 0;
};

#endif