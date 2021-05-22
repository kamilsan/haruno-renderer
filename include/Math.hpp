#ifndef MATH_HPP
#define MATH_HPP

#include <cmath>

#define PI 3.14159265358979323846
#define TAU 6.28318530717958647692
#define ONE_OVER_PI 0.31830988618379067154
#define HALF_PI 1.57079632679489661923

inline float toRadians(float angle)
{
  return PI * angle / 180.0f;
}

#endif