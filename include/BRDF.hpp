#ifndef BRDF_HPP
#define BRDF_HPP

#include "Color.hpp"
#include "RNG.hpp"
#include "Vector3.hpp"

class BRDF {
 public:
  enum class Type { Regular, PerfectSpecular };

  virtual Type getType() const = 0;
  virtual float sample(const Vector3f& wo, RNG& rng, Vector3f& wi, float& pdf) const = 0;
  virtual Color evaluate(const Vector3f& wi, const Vector3f& wo) const = 0;
};

#endif