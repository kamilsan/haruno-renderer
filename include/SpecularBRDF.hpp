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
  inline Float sample(const Vector3t& wo, RNG& rng, Vector3t& wi, Float& pdf) const override;
  inline Color evaluate(const Vector3t& wi, const Vector3t& wo) const override;
};

Float SpecularBRDF::sample(const Vector3t& wo, RNG&, Vector3t& wi, Float& pdf) const {
  wi = Vector3t(-wo.x, wo.y, -wo.z);
  pdf = 1.0;

  return 1.0 / std::fabs(wi.y);
}

Color SpecularBRDF::evaluate(const Vector3t&, const Vector3t&) const { return 0.0; }

#endif