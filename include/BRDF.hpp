#ifndef BRDF_HPP
#define BRDF_HPP

#include "Color.hpp"
#include "RNG.hpp"
#include "Vector.hpp"

class BRDF {
 public:
  enum class Type { Regular, PerfectSpecular };

  virtual Type getType() const = 0;
  virtual float sample(const Vector& wo, RNG& rng, Vector& wi, float& pdf) const = 0;
  virtual Color evaluate(const Vector& wi, const Vector& wo) const = 0;
};

#endif