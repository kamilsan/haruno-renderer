#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cmath>
#include <iostream>

class Vector
{
public:
  float x, y, z;

  Vector(): x(0), y(0), z(0) {}
  Vector(const float xx, const float yy, const float zz): x(xx), y(yy), z(zz) {}

  float lengthSq() const { return x * x + y * y + z * z; }
  float length() const { return sqrtf(lengthSq()); }
  
  float dot(const Vector &other) const { return x * other.x + y * other.y + z * other.z; }
  Vector cross(const Vector &other) const { return Vector(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x); }
  
  Vector normalized() const;
  Vector clamped(float min = 0.0f, float max = 1.0f) const;

  bool operator==(const Vector& other) const { return x == other.x && y == other.y && z == other.z; }
  bool operator!=(const Vector& other) const { return x != other.x || y != other.y || z != other.z; }

  Vector operator-() const { return Vector(-x, -y, -z); }
  Vector operator+(const Vector &other) const { return Vector(x + other.x, y + other.y, z + other.z); }
  
  Vector& operator+=(const Vector &other)
  {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
  }

  Vector operator-(const Vector &other) const { return Vector(x - other.x, y - other.y, z - other.z); }
  
  Vector& operator-=(const Vector &other)
  {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
  }
  Vector operator*(const float r) const { return Vector(x * r, y * r, z * r); }
  
  Vector& operator*=(const float r)
  {
    x *= r;
    y *= r;
    z *= r;
    return *this;
  }

  Vector& operator*=(const Vector& v)
  {
    x *= v.x;
    y *= v.y;
    z *= v.z;
    return *this;
  }

  Vector operator*(const Vector &other) const { return Vector(x * other.x, y * other.y, z * other.z); }
  Vector operator/(const float r) const { const float f = 1.0f/r; return Vector(x * f, y * f, z * f); }
  
  Vector& operator/=(const float r) 
  { 
    const float f = 1.0f/r;
    x *= f;
    y *= f;
    z *= f;
    return *this; 
  }
  Vector& operator/=(const Vector& v) 
  { 
    x /= v.x;
    y /= v.y;
    z /= v.z;
    return *this; 
  }


  friend std::ostream& operator<<(std::ostream& os, const Vector& v)
  {
     return os << "<" << v.x << ", " << v.y << ", " << v.z << ">";
  }

  friend Vector operator*(const float r, const Vector& v)
  {
     return v*r;
  }
};

#endif