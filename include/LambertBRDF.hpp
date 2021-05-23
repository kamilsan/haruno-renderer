#ifndef LAMBERT_BRDF_HPP
#define LAMBERT_BRDF_HPP

#include "BRDF.hpp"
#include "Vector.hpp"
#include "Color.hpp"
#include "Math.hpp"
#include "RNG.hpp"

class LambertBRDF : public BRDF
{
public:
  LambertBRDF(float diffuseFactor): diffuseFactor_(diffuseFactor) {}

  float getDiffuseFactor() const { return diffuseFactor_; }

  inline float sample(const Vector& wo, RNG& rng, Vector& wi, float& pdf) const override;
  inline Color evaluate(const Vector& wi, const Vector& wo) const override;

private:
  float diffuseFactor_;
};

float LambertBRDF::sample(const Vector&, RNG& rng, Vector& wi, float& pdf) const
{
  const float sinTheta = std::sqrt(rng.get());
  const float cosTheta = std::sqrt(1.0f - sinTheta * sinTheta);

  float phi = TAU * rng.get();
  
  wi = Vector(sinTheta * std::cos(phi), cosTheta, sinTheta * std::sin(phi));
  pdf = cosTheta * ONE_OVER_PI;

  return diffuseFactor_ * ONE_OVER_PI;
}

Color LambertBRDF::evaluate(const Vector&, const Vector&) const 
{
  return diffuseFactor_ * ONE_OVER_PI; 
}

#endif