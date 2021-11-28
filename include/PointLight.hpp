#ifndef POINT_LIGHT_HPP
#define POINT_LIGHT_HPP

#include "Color.hpp"
#include "Light.hpp"
#include "Vector3.hpp"

class PointLight : public Light {
 public:
  PointLight(const Vector3f& position, const Color& color, float intensity)
      : position_(position), color_(color), intensity_(intensity) {}

  Color evaluate(const Vector3f& position) const override;
  Ray getShadowRay(const Vector3f& position, float& maxT) const override;

  const Vector3f& getPosition() const { return position_; }
  const Color& getColor() const { return color_; }
  float getIntensity() const { return intensity_; }

 private:
  Vector3f position_;
  Color color_;
  float intensity_;
};

Color PointLight::evaluate(const Vector3f& position) const {
  const auto lengthSq = (position_ - position).lengthSq();
  return (intensity_ / lengthSq) * color_;
}

Ray PointLight::getShadowRay(const Vector3f& position, float& maxT) const {
  auto toLight = position_ - position;
  const auto len = toLight.length();
  toLight /= len;

  const Vector3f origin = position + toLight * 0.001f;

  maxT = len;
  return Ray{origin, toLight};
}

#endif