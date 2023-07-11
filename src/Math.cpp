#include "Math.hpp"

#include "Vector3.hpp"

// Method by Tom Duff et al.
void createOrthogonalFrame(const Vector3t& normal, Vector3t& tangent, Vector3t& bitangent) {
  const Float sign = std::copysignf(1.0, normal.z);
  const Float a = -1.0 / (sign + normal.z);
  const Float b = normal.x * normal.y * a;
  tangent = Vector3t(1.0 + sign * normal.x * normal.x * a, sign * b, -sign * normal.x);
  bitangent = Vector3t(b, sign + normal.y * normal.y * a, -normal.y);
}

bool solveQuadratic(Float a, Float b, Float c, Float& t1, Float& t2) {
  Float delta = b * b - 4.0 * a * c;

  if (delta < 0.0) {
    return false;
  }

  delta = std::sqrt(delta);

  const Float q = -0.5 * (b + std::copysign(1.0, b) * delta);

  t1 = q / a;
  t2 = c / q;

  if (t2 < t1) {
    std::swap(t1, t2);
  }

  return true;
}

Vector3t transformToTangentSpace(const Vector3t& v, const Vector3t& normal, const Vector3t& tangent,
                                 const Vector3t& bitangent) {
  const Vector3t transformed{v.x * tangent.x + v.y * normal.x + v.z * bitangent.x,
                             v.x * tangent.y + v.y * normal.y + v.z * bitangent.y,
                             v.x * tangent.z + v.y * normal.z + v.z * bitangent.z};

  return transformed;
}

Vector3t transformFromTangentSpace(const Vector3t& v, const Vector3t& normal,
                                   const Vector3t& tangent, const Vector3t& bitangent) {
  const Vector3t transformed{v.x * tangent.x + v.y * tangent.y + v.z * tangent.z,
                             v.x * normal.x + v.y * normal.y + v.z * normal.z,
                             v.x * bitangent.x + v.y * bitangent.y + v.z * bitangent.z};

  return transformed;
}