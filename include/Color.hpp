#ifndef COLOR_HPP
#define COLOR_HPP

#include <iostream>

#include "Types.hpp"

struct Color {
  Color(Float r, Float g, Float b) : r(r), g(g), b(b) {}
  Color(Float v) : r(v), g(v), b(v) {}
  Color() : r(0), g(0), b(0) {}

  bool operator==(const Color& other) const { return r == other.r && g == other.g && b == other.b; }
  bool operator!=(const Color& other) const { return !operator==(other); }

  Color operator+(const Color& other) const { return {r + other.r, g + other.g, b + other.b}; }

  Color operator-(const Color& other) const { return {r - other.r, g - other.g, b - other.b}; }

  Color operator*(const Color& other) const { return {r * other.r, g * other.g, b * other.b}; }

  Color operator*(Float weight) const { return {r * weight, g * weight, b * weight}; }

  Color operator/(Float weight) const {
    const Float f = 1.0 / weight;
    return {r * f, g * f, b * f};
  }

  Color& operator+=(const Color& other) {
    r += other.r;
    g += other.g;
    b += other.b;

    return *this;
  }

  Color& operator-=(const Color& other) {
    r -= other.r;
    g -= other.g;
    b -= other.b;

    return *this;
  }

  Color& operator*=(const Color& other) {
    r *= other.r;
    g *= other.g;
    b *= other.b;

    return *this;
  }

  Color& operator*=(Float weight) {
    r *= weight;
    g *= weight;
    b *= weight;

    return *this;
  }

  Color& operator/=(Float weight) {
    const Float f = 1.0 / weight;

    r *= f;
    g *= f;
    b *= f;

    return *this;
  }

  friend std::ostream& operator<<(std::ostream& os, const Color& c) {
    return os << "(" << c.r << ", " << c.g << ", " << c.b << ")";
  }

  friend Color operator*(Float weight, const Color& color) { return color * weight; }

  friend Color operator/(Float weight, const Color& color) { return color / weight; }

  Float r;
  Float g;
  Float b;
};

#endif