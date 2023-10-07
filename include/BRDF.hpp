#ifndef BRDF_HPP
#define BRDF_HPP

#include "Color.hpp"
#include "RNG.hpp"
#include "Types.hpp"

class BRDF {
 public:
  enum class Type { Regular, PerfectSpecular };

  virtual ~BRDF() = default;

  virtual Type getType() const = 0;
  virtual Float sample(const Vector3t& wo, RNG& rng, Vector3t& wi, Float& pdf) const = 0;
  virtual Color evaluate(const Vector3t& wi, const Vector3t& wo) const = 0;
};

#endif