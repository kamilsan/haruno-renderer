#ifndef VECTOR3_HPP
#define VECTOR3_HPP

#include <cmath>
#include <iostream>

template <typename T>
class Vector3 {
 public:
  Vector3() : x(0), y(0), z(0) {}
  explicit Vector3(const T v) : x(v), y(v), z(v) {}
  Vector3(const T xx, const T yy, const T zz) : x(xx), y(yy), z(zz) {}

  T lengthSq() const { return x * x + y * y + z * z; }
  T length() const { return sqrtf(lengthSq()); }

  T dot(const Vector3& other) const { return x * other.x + y * other.y + z * other.z; }
  Vector3 cross(const Vector3& other) const {
    return Vector3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
  }

  const T& operator[](size_t i) const {
    if (i == 0)
      return x;
    else if (i == 1)
      return y;
    return z;
  }

  T& operator[](size_t i) {
    if (i == 0)
      return x;
    else if (i == 1)
      return y;
    return z;
  }

  Vector3 normalized() const;
  Vector3 clamped(T min = 0.0, T max = 1.0) const;

  bool operator==(const Vector3& other) const {
    return x == other.x && y == other.y && z == other.z;
  }
  bool operator!=(const Vector3& other) const {
    return x != other.x || y != other.y || z != other.z;
  }

  Vector3 operator-() const { return Vector3(-x, -y, -z); }
  Vector3 operator+(const Vector3& other) const {
    return Vector3(x + other.x, y + other.y, z + other.z);
  }

  Vector3& operator+=(const Vector3& other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
  }

  Vector3 operator-(const Vector3& other) const {
    return Vector3(x - other.x, y - other.y, z - other.z);
  }

  Vector3& operator-=(const Vector3& other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
  }
  Vector3 operator*(const T r) const { return Vector3(x * r, y * r, z * r); }

  Vector3& operator*=(const T r) {
    x *= r;
    y *= r;
    z *= r;
    return *this;
  }

  Vector3& operator*=(const Vector3& v) {
    x *= v.x;
    y *= v.y;
    z *= v.z;
    return *this;
  }

  Vector3 operator*(const Vector3& other) const {
    return Vector3(x * other.x, y * other.y, z * other.z);
  }
  Vector3 operator/(const T r) const {
    const T f = 1.0 / r;
    return Vector3(x * f, y * f, z * f);
  }

  Vector3& operator/=(const T r) {
    const T f = 1.0 / r;
    x *= f;
    y *= f;
    z *= f;
    return *this;
  }
  Vector3& operator/=(const Vector3& v) {
    x /= v.x;
    y /= v.y;
    z /= v.z;
    return *this;
  }

  friend std::ostream& operator<<(std::ostream& os, const Vector3& v) {
    return os << "<" << v.x << ", " << v.y << ", " << v.z << ">";
  }

  friend Vector3 operator*(const T r, const Vector3& v) { return v * r; }

  T x;
  T y;
  T z;
};

template <typename T>
Vector3<T> Vector3<T>::normalized() const {
  const T len = length();
  if (len > 0.00001) {
    const T f = 1.0 / len;
    return Vector3{x * f, y * f, z * f};
  }
  return Vector3{};
}

template <typename T>
Vector3<T> Vector3<T>::clamped(T min, T max) const {
  T newX = x;
  T newY = y;
  T newZ = z;

  if (newX < min)
    newX = min;
  else if (newX > max)
    newX = max;

  if (newY < min)
    newY = min;
  else if (newY > max)
    newY = max;

  if (newZ < min)
    newZ = min;
  else if (newZ > max)
    newZ = max;

  return Vector3{newX, newY, newZ};
}

typedef Vector3<float> Vector3f;
typedef Vector3<double> Vector3d;

#endif  // VECTOR3_HPP