#ifndef COLOR_HPP
#define COLOR_HPP

struct Color
{
  Color(float r, float g, float b): r(r), g(g), b(b) {}
  Color(float v): r(v), g(v), b(v) {}
  Color(): r(0), g(0), b(0) {}

  bool operator==(const Color& other) const { return r == other.r && g == other.g && b == other.b; }
  bool operator!=(const Color& other) const { return !operator==(other); }

  Color operator+(const Color& other) const
  {
    return {r + other.r, g + other.g, b + other.b};
  }

  Color operator-(const Color& other) const
  {
    return {r - other.r, g - other.g, b - other.b};
  }

  Color operator*(float weight) const
  {
    return {r * weight, g * weight, b * weight};
  }

  Color operator/(float weight) const
  {
    const float f = 1.0 / weight;
    return {r * f, g * f, b * f};
  }

  Color& operator+=(const Color& other)
  {
    r += other.r;
    g += other.g;
    b += other.b;

    return *this;
  }

  Color& operator-=(const Color& other)
  {
    r -= other.r;
    g -= other.g;
    b -= other.b;

    return *this;
  }

  Color& operator*=(float weight)
  {
    r *= weight;
    g *= weight;
    b *= weight;

    return *this;
  }

  Color& operator/=(float weight)
  {
    const float f = 1.0 / weight;

    r *= f;
    g *= f;
    b *= f;

    return *this;
  }

  friend Color operator*(float weight, const Color& color)
  {
    return color*weight;
  }

  friend Color operator/(float weight, const Color& color)
  {
    return color/weight;
  }

  float r;
  float g;
  float b;
};

#endif