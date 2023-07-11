#ifndef MATH_HPP
#define MATH_HPP

#include <cmath>

#include "Types.hpp"

#define PI 3.14159265358979323846
#define TAU 6.28318530717958647692
#define ONE_OVER_PI 0.31830988618379067154
#define HALF_PI 1.57079632679489661923
#define EPSILON 0.00001

inline Float toRadians(Float angle) { return PI * angle / 180.0; }

bool solveQuadratic(Float a, Float b, Float c, Float& t1, Float& t2);

// Method by Tom Duff et al.
void createOrthogonalFrame(const Vector3t& normal, Vector3t& tangent, Vector3t& bitangent);

Vector3t transformToTangentSpace(const Vector3t& v, const Vector3t& normal, const Vector3t& tangent,
                                 const Vector3t& bitangent);
Vector3t transformFromTangentSpace(const Vector3t& v, const Vector3t& normal,
                                   const Vector3t& tangent, const Vector3t& bitangent);

#endif