#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include <cmath>
#include <iostream>

template <typename T>
class Vector2 {
 public:
  Vector2() : x(0), y(0) {}
  explicit Vector2(const T v) : x(v), y(v) {}
  Vector2(const T xx, const T yy) : x(xx), y(yy) {}

  T lengthSq() const { return x * x + y * y; }
  T length() const { return sqrtf(lengthSq()); }

  T dot(const Vector2& other) const { return x * other.x + y * other.y; }

  const T& operator[](size_t i) const {
    if (i == 0) return x;
    return y;
  }

  T& operator[](size_t i) {
    if (i == 0) return x;
    return y;
  }

  Vector2 normalized() const;
  Vector2 clamped(T min = 0.0, T max = 1.0) const;

  bool operator==(const Vector2& other) const { return x == other.x && y == other.y; }
  bool operator!=(const Vector2& other) const { return x != other.x || y != other.y; }

  Vector2 operator-() const { return Vector2(-x, -y); }
  Vector2 operator+(const Vector2& other) const { return Vector2(x + other.x, y + other.y); }

  Vector2& operator+=(const Vector2& other) {
    x += other.x;
    y += other.y;
    return *this;
  }

  Vector2 operator-(const Vector2& other) const { return Vector2(x - other.x, y - other.y); }

  Vector2& operator-=(const Vector2& other) {
    x -= other.x;
    y -= other.y;
    return *this;
  }
  Vector2 operator*(const T r) const { return Vector2(x * r, y * r); }

  Vector2& operator*=(const T r) {
    x *= r;
    y *= r;
    return *this;
  }

  Vector2& operator*=(const Vector2& v) {
    x *= v.x;
    y *= v.y;
    return *this;
  }

  Vector2 operator*(const Vector2& other) const { return Vector2(x * other.x, y * other.y); }
  Vector2 operator/(const T r) const {
    const T f = 1.0 / r;
    return Vector2(x * f, y * f);
  }

  Vector2& operator/=(const T r) {
    const T f = 1.0 / r;
    x *= f;
    y *= f;
    return *this;
  }
  Vector2& operator/=(const Vector2& v) {
    x /= v.x;
    y /= v.y;
    return *this;
  }

  friend std::ostream& operator<<(std::ostream& os, const Vector2& v) {
    return os << "<" << v.x << ", " << v.y << ">";
  }

  friend Vector2 operator*(const T r, const Vector2& v) { return v * r; }

  T x;
  T y;
};

template <typename T>
Vector2<T> Vector2<T>::normalized() const {
  const T len = length();
  if (len > 0.00001) {
    const T f = 1.0 / len;
    return Vector2{x * f, y * f};
  }
  return Vector2{};
}

template <typename T>
Vector2<T> Vector2<T>::clamped(T min, T max) const {
  T newX = x;
  T newY = y;

  if (newX < min)
    newX = min;
  else if (newX > max)
    newX = max;

  if (newY < min)
    newY = min;
  else if (newY > max)
    newY = max;

  return Vector2{newX, newY};
}

#endif  // VECTOR2_HPP