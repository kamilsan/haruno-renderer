#include "SimpleEnvironment.hpp"

#include "Math.hpp"
#include "Vector.hpp"

Color SimpleEnvironment::getColor(const Vector& direction) const {
  const float theta = std::asin(direction.y);

  if (theta > 0) {
    const float lerpFactor = std::pow(theta / HALF_PI, 1.0 / 2.5f);

    const Color sky = lerpFactor * zenithColor_ + (1.0f - lerpFactor) * horizonColor_;
    return sky;
  } else
    return groundColor_;
}