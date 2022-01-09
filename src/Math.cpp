#include "Math.hpp"

#include "Vector3.hpp"

// Method by Tom Duff et al.
void createOrthogonalFrame(const Vector3f& normal, Vector3f& tangent, Vector3f& bitangent) {
  const float sign = std::copysignf(1.0f, normal.z);
  const float a = -1.0f / (sign + normal.z);
  const float b = normal.x * normal.y * a;
  tangent = Vector3f(1.0f + sign * normal.x * normal.x * a, sign * b, -sign * normal.x);
  bitangent = Vector3f(b, sign + normal.y * normal.y * a, -normal.y);
}

bool solveQuadratic(float a, float b, float c, float& t1, float& t2) {
  float delta = b * b - 4.0f * a * c;

  if (delta < 0.0f) {
    return false;
  }

  delta = std::sqrt(delta);

  const float q = -0.5f * (b + std::copysign(1.0f, b) * delta);

  t1 = q / a;
  t2 = c / q;

  if (t2 < t1) {
    std::swap(t1, t2);
  }

  return true;
}

Vector3f transformToTangentSpace(const Vector3f& v, const Vector3f& normal, const Vector3f& tangent,
                                 const Vector3f& bitangent) {
  const Vector3f transformed{v.x * tangent.x + v.y * normal.x + v.z * bitangent.x,
                             v.x * tangent.y + v.y * normal.y + v.z * bitangent.y,
                             v.x * tangent.z + v.y * normal.z + v.z * bitangent.z};

  return transformed;
}

Vector3f transformFromTangentSpace(const Vector3f& v, const Vector3f& normal,
                                   const Vector3f& tangent, const Vector3f& bitangent) {
  const Vector3f transformed{v.x * tangent.x + v.y * tangent.y + v.z * tangent.z,
                             v.x * normal.x + v.y * normal.y + v.z * normal.z,
                             v.x * bitangent.x + v.y * bitangent.y + v.z * bitangent.z};

  return transformed;
}