#ifndef LAMBERT_BRDF_HPP
#define LAMBERT_BRDF_HPP

#include "BRDF.hpp"
#include "Vector.hpp"
#include "Color.hpp"

#include <cmath>

class LambertBRDF : public BRDF
{
public:
  LambertBRDF() = default;

  inline Color evaluate(const Vector& wi, const Vector& wo) const override;
};

Color LambertBRDF::evaluate(const Vector&, const Vector&) const 
{
  return M_1_PI; 
}

#endif