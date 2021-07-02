#ifndef DIRECTIONAL_LIGHT_HPP
#define DIRECTIONAL_LIGHT_HPP

#include "Color.hpp"
#include "Light.hpp"
#include "Vector.hpp"

class DirectionalLight : public Light {
 public:
  DirectionalLight(const Vector& direction, const Color& color, float intensity)
      : direction_(direction.normalized()), color_(color), intensity_(intensity) {}

  Color evaluate(const Vector& position) const override;
  Ray getShadowRay(const Vector& position, float& maxT) const override;

  const Vector& getDirection() const { return direction_; }
  const Color& getColor() const { return color_; }
  float getIntensity() const { return intensity_; }

 private:
  Vector direction_;
  Color color_;
  float intensity_;
};

Color DirectionalLight::evaluate(const Vector&) const { return intensity_ * color_; }

Ray DirectionalLight::getShadowRay(const Vector& position, float& maxT) const {
  const Vector origin = position - direction_ * 0.001f;
  maxT = -1.0f;

  return Ray{origin, -direction_};
}

#endif