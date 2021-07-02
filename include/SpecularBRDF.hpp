#ifndef SPECULAR_BRDF_HPP
#define SPECULAR_BRDF_HPP

#include "BRDF.hpp"
#include "Color.hpp"
#include "Math.hpp"
#include "RNG.hpp"
#include "Vector.hpp"

class SpecularBRDF : public BRDF {
 public:
  SpecularBRDF() = default;

  inline float sample(const Vector& wo, RNG& rng, Vector& wi, float& pdf) const override;
  inline Color evaluate(const Vector& wi, const Vector& wo) const override;
};

float SpecularBRDF::sample(const Vector& wo, RNG&, Vector& wi, float& pdf) const {
  wi = Vector(-wo.x, wo.y, -wo.z);
  pdf = 1.0f;

  return 1.0f / std::fabs(wi.y);
}

Color SpecularBRDF::evaluate(const Vector&, const Vector&) const { return 0.0f; }

#endif