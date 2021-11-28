#ifndef SPECULAR_BRDF_HPP
#define SPECULAR_BRDF_HPP

#include "BRDF.hpp"
#include "Color.hpp"
#include "Math.hpp"
#include "RNG.hpp"
#include "Vector3.hpp"

class SpecularBRDF : public BRDF {
 public:
  SpecularBRDF() = default;

  inline Type getType() const override { return Type::PerfectSpecular; }
  inline float sample(const Vector3f& wo, RNG& rng, Vector3f& wi, float& pdf) const override;
  inline Color evaluate(const Vector3f& wi, const Vector3f& wo) const override;
};

float SpecularBRDF::sample(const Vector3f& wo, RNG&, Vector3f& wi, float& pdf) const {
  wi = Vector3f(-wo.x, wo.y, -wo.z);
  pdf = 1.0f;

  return 1.0f / std::fabs(wi.y);
}

Color SpecularBRDF::evaluate(const Vector3f&, const Vector3f&) const { return 0.0f; }

#endif