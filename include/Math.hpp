#ifndef MATH_HPP
#define MATH_HPP

#include <cmath>

#include "Vector3.hpp"

#define PI 3.14159265358979323846
#define TAU 6.28318530717958647692
#define ONE_OVER_PI 0.31830988618379067154
#define HALF_PI 1.57079632679489661923
#define EPSILON 0.00001f

inline float toRadians(float angle) { return PI * angle / 180.0f; }

// Method by Tom Duff et al.
void createOrthogonalFrame(const Vector3f& normal, Vector3f& tangent, Vector3f& bitangent);

Vector3f transformToTangentSpace(const Vector3f& v, const Vector3f& normal, const Vector3f& tangent,
                                 const Vector3f& bitangent);
Vector3f transformFromTangentSpace(const Vector3f& v, const Vector3f& normal,
                                   const Vector3f& tangent, const Vector3f& bitangent);

#endif