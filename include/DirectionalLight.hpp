#ifndef DIRECTIONAL_LIGHT_HPP
#define DIRECTIONAL_LIGHT_HPP

#include "Color.hpp"
#include "Light.hpp"
#include "Vector3.hpp"

class DirectionalLight : public Light {
 public:
  DirectionalLight(const Vector3f& direction, const Color& color, float intensity)
      : direction_(direction.normalized()), color_(color), intensity_(intensity) {}

  Color evaluate(const Vector3f& position) const override;
  Ray getShadowRay(const Vector3f& position, float& maxT) const override;
  bool isDelta() const override { return true; };

  Color sampleLe(Vector3f&, SurfaceInfo&, RNG&, float&) const override { return {}; }

  const Vector3f& getDirection() const { return direction_; }
  const Color& getColor() const { return color_; }
  float getIntensity() const { return intensity_; }

 private:
  Vector3f direction_;
  Color color_;
  float intensity_;
};

Color DirectionalLight::evaluate(const Vector3f&) const { return intensity_ * color_; }

Ray DirectionalLight::getShadowRay(const Vector3f& position, float& maxT) const {
  const Vector3f origin = position - direction_ * 0.001f;
  maxT = -1.0f;

  return Ray{origin, -direction_};
}

#endif