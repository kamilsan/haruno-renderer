#ifndef MATH_HPP
#define MATH_HPP

#include <cmath>

class Vector;

#define PI 3.14159265358979323846
#define TAU 6.28318530717958647692
#define ONE_OVER_PI 0.31830988618379067154
#define HALF_PI 1.57079632679489661923

inline float toRadians(float angle)
{
  return PI * angle / 180.0f;
}

// Method by Tom Duff et al.
void createOrthogonalFrame(const Vector& normal, Vector& tangent, Vector& bitangent);

Vector transformToTangentSpace(const Vector& v, const Vector& normal, const Vector& tangent, const Vector& bitangent);
Vector transformFromTangentSpace(const Vector& v, const Vector& normal, const Vector& tangent, const Vector& bitangent);

#endif