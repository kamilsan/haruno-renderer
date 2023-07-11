#ifndef POINT_LIGHT_HPP
#define POINT_LIGHT_HPP

#include "Color.hpp"
#include "Light.hpp"
#include "Vector3.hpp"

class PointLight : public Light {
 public:
  PointLight(const Vector3t& position, const Color& color, Float intensity)
      : position_(position), color_(color), intensity_(intensity) {}

  Color evaluate(const Vector3t& position) const override;
  Ray getShadowRay(const Vector3t& position, Float& maxT) const override;
  bool isDelta() const override { return true; }
  Color sampleLe(Vector3t&, SurfaceInfo&, RNG&, Float&) const override { return {}; }

  const Vector3t& getPosition() const { return position_; }
  const Color& getColor() const { return color_; }
  Float getIntensity() const { return intensity_; }

 private:
  Vector3t position_;
  Color color_;
  Float intensity_;
};

Color PointLight::evaluate(const Vector3t& position) const {
  const auto lengthSq = (position_ - position).lengthSq();
  return (intensity_ / lengthSq) * color_;
}

Ray PointLight::getShadowRay(const Vector3t& position, Float& maxT) const {
  auto toLight = position_ - position;
  const auto len = toLight.length();
  toLight /= len;

  const Vector3t origin = position + toLight * 0.001;

  maxT = len;
  return Ray{origin, toLight};
}

#endif