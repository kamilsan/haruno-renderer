#ifndef DIRECTIONAL_LIGHT_HPP
#define DIRECTIONAL_LIGHT_HPP

#include "Color.hpp"
#include "Light.hpp"
#include "Vector3.hpp"

class DirectionalLight : public Light {
 public:
  DirectionalLight(const Vector3t& direction, const Color& color, Float intensity)
      : direction_(direction.normalized()), color_(color), intensity_(intensity) {}

  Color evaluate(const Vector3t& position) const override;
  Ray getShadowRay(const Vector3t& position, Float& maxT) const override;
  bool isDelta() const override { return true; };

  Color sampleLe(Vector3t&, SurfaceInfo&, RNG&, Float&) const override { return {}; }

  const Vector3t& getDirection() const { return direction_; }
  const Color& getColor() const { return color_; }
  Float getIntensity() const { return intensity_; }

 private:
  Vector3t direction_;
  Color color_;
  Float intensity_;
};

Color DirectionalLight::evaluate(const Vector3t&) const { return intensity_ * color_; }

Ray DirectionalLight::getShadowRay(const Vector3t& position, Float& maxT) const {
  const Vector3t origin = position - direction_ * 0.001;
  maxT = -1.0;

  return Ray{origin, -direction_};
}

#endif