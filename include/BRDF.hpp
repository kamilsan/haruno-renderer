#ifndef BRDF_HPP
#define BRDF_HPP

#include "Color.hpp"
#include "Vector.hpp"
#include "RNG.hpp"

class BRDF
{
public:
  virtual float sample(const Vector& wo, RNG& rng, Vector& wi, float& pdf) const = 0;
  virtual Color evaluate(const Vector& wi, const Vector& wo) const = 0;
};

#endif