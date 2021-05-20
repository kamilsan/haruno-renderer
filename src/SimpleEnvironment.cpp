#include "SimpleEnvironment.hpp"

#include "Vector.hpp"

#include <cmath>

Color SimpleEnvironment::getColor(const Vector& direction) const
{
  const float phi = std::atan(direction.y / direction.z);

  if(phi > 0)
  {
    const float lerpFactor = std::pow(phi / M_PI_2, 1.0 / 2.5f);

    const Color sky = lerpFactor * zenithColor_ + (1.0f - lerpFactor) * horizonColor_;
    return sky;
  }
  else
    return groundColor_;
}