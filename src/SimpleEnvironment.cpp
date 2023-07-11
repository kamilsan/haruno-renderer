#include "SimpleEnvironment.hpp"

#include "Math.hpp"
#include "Vector3.hpp"

Color SimpleEnvironment::getColor(const Vector3t& direction) const {
  const Float theta = std::asin(direction.y);

  if (theta > 0) {
    const Float lerpFactor = std::pow(theta / HALF_PI, 1.0 / 2.5);

    const Color sky = lerpFactor * zenithColor_ + (1.0 - lerpFactor) * horizonColor_;
    return sky;
  } else
    return groundColor_;
}