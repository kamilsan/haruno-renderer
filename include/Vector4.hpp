#ifndef VECTOR4_HPP
#define VECTOR4_HPP

#include <cmath>

#include "Vector3.hpp"

template <typename T>
class Vector4 {
 public:
  Vector4() : x(0), y(0), z(0), w(0) {}
  explicit Vector4(T v) : x(v), y(v), z(v), w(v) {}
  Vector4(const T xx, const T yy, const T zz, const T ww) : x(xx), y(yy), z(zz), w(ww) {}
  Vector4(const Vector3<T>& vector3, const T ww)
      : x(vector3.x), y(vector3.y), z(vector3.z), w(ww) {}

  T lengthSq() const { return x * x + y * y + z * z + w * w; }
  T length() const { return sqrtf(lengthSq()); }
  T dot(const Vector4& other) const {
    return x * other.x + y * other.y + z * other.z + w * other.w;
  }

  Vector4 normalized() const;
  Vector4 clamped(T min = 0.0, T max = 1.0) const;

  const T& operator[](size_t i) const {
    if (i == 0)
      return x;
    else if (i == 1)
      return y;
    else if (i == 2)
      return z;
    return w;
  }

  T& operator[](size_t i) {
    if (i == 0)
      return x;
    else if (i == 1)
      return y;
    else if (i == 2)
      return z;
    return w;
  }

  explicit operator Vector3<T>() const { return Vector3<T>(x, y, z); }

  bool operator==(const Vector4& other) const {
    return x == other.x && y == other.y && z == other.z && w == other.w;
  }
  bool operator!=(const Vector4& other) const {
    return x != other.x || y != other.y || z != other.z || w != other.w;
  }

  Vector4 operator-() const { return Vector4(-x, -y, -z, -w); }
  Vector4 operator+(const Vector4& other) const {
    return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
  }

  Vector4& operator+=(const Vector4& other) {
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;
    return *this;
  }

  Vector4 operator-(const Vector4& other) const {
    return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
  }

  Vector4& operator-=(const Vector4& other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    w -= other.w;
    return *this;
  }
  Vector4 operator*(const T r) const { return Vector4(x * r, y * r, z * r, w * r); }

  Vector4& operator*=(const T r) {
    x *= r;
    y *= r;
    z *= r;
    w *= r;
    return *this;
  }

  Vector4& operator*=(const Vector4& v) {
    x *= v.x;
    y *= v.y;
    z *= v.z;
    w *= v.w;
    return *this;
  }

  Vector4 operator*(const Vector4& other) const {
    return Vector4(x * other.x, y * other.y, z * other.z, w * other.w);
  }
  Vector4 operator/(const T r) const {
    const T f = 1.0 / r;
    return Vector4(x * f, y * f, z * f, w * f);
  }

  Vector4& operator/=(const T r) {
    const T f = 1.0 / r;
    x *= f;
    y *= f;
    z *= f;
    w *= f;
    return *this;
  }
  Vector4& operator/=(const Vector4& v) {
    x /= v.x;
    y /= v.y;
    z /= v.z;
    w /= v.w;
    return *this;
  }

  friend std::ostream& operator<<(std::ostream& os, const Vector4& v) {
    return os << "<" << v.x << ", " << v.y << ", " << v.z << "," << v.w << ">";
  }

  friend Vector4 operator*(const T r, const Vector4& v) { return v * r; }

  T x;
  T y;
  T z;
  T w;
};

template <typename T>
Vector4<T> Vector4<T>::normalized() const {
  const T len = length();
  if (len > 0.00001) {
    const T f = 1.0 / len;
    return Vector4{x * f, y * f, z * f, w * f};
  }
  return Vector4{};
}

template <typename T>
Vector4<T> Vector4<T>::clamped(T min, T max) const {
  T newX = x;
  T newY = y;
  T newZ = z;
  T newW = w;

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

  if (newW < min)
    newW = min;
  else if (newW > max)
    newW = max;

  return Vector4{newX, newY, newZ, newW};
}

#endif  // VECTOR4_HPP