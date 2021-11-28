#ifndef LAMBERT_BRDF_HPP
#define LAMBERT_BRDF_HPP

#include "BRDF.hpp"
#include "Color.hpp"
#include "Math.hpp"
#include "RNG.hpp"
#include "Vector3.hpp"

class LambertBRDF : public BRDF {
 public:
  LambertBRDF(float diffuseFactor) : diffuseFactor_(diffuseFactor) {}

  float getDiffuseFactor() const { return diffuseFactor_; }

  inline Type getType() const override { return Type::Regular; }
  inline float sample(const Vector3f& wo, RNG& rng, Vector3f& wi, float& pdf) const override;
  inline Color evaluate(const Vector3f& wi, const Vector3f& wo) const override;

 private:
  float diffuseFactor_;
};

float LambertBRDF::sample(const Vector3f&, RNG& rng, Vector3f& wi, float& pdf) const {
  const float sinTheta = std::sqrt(rng.get());
  const float cosTheta = std::sqrt(1.0f - sinTheta * sinTheta);

  float phi = TAU * rng.get();

  wi = Vector3f(sinTheta * std::cos(phi), cosTheta, sinTheta * std::sin(phi));
  pdf = cosTheta * ONE_OVER_PI;

  return diffuseFactor_ * ONE_OVER_PI;
}

Color LambertBRDF::evaluate(const Vector3f&, const Vector3f&) const {
  return diffuseFactor_ * ONE_OVER_PI;
}

#endif