#ifndef LAMBERT_BRDF_HPP
#define LAMBERT_BRDF_HPP

#include "BRDF.hpp"
#include "Color.hpp"
#include "Math.hpp"
#include "RNG.hpp"
#include "Vector3.hpp"

class LambertBRDF : public BRDF {
 public:
  LambertBRDF(Float diffuseFactor) : diffuseFactor_(diffuseFactor) {}

  Float getDiffuseFactor() const { return diffuseFactor_; }

  inline Type getType() const override { return Type::Regular; }
  inline Float sample(const Vector3t& wo, RNG& rng, Vector3t& wi, Float& pdf) const override;
  inline Color evaluate(const Vector3t& wi, const Vector3t& wo) const override;

 private:
  Float diffuseFactor_;
};

Float LambertBRDF::sample(const Vector3t&, RNG& rng, Vector3t& wi, Float& pdf) const {
  const Float sinTheta = std::sqrt(rng.get());
  const Float cosTheta = std::sqrt(1.0 - sinTheta * sinTheta);

  Float phi = TAU * rng.get();

  wi = Vector3t(sinTheta * std::cos(phi), cosTheta, sinTheta * std::sin(phi));
  pdf = cosTheta * ONE_OVER_PI;

  return diffuseFactor_ * ONE_OVER_PI;
}

Color LambertBRDF::evaluate(const Vector3t&, const Vector3t&) const {
  return diffuseFactor_ * ONE_OVER_PI;
}

#endif