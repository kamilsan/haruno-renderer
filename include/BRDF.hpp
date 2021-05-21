#ifndef BRDF_HPP
#define BRDF_HPP

#include "Color.hpp"

class Vector;

class BRDF
{
public:
  virtual Color evaluate(const Vector& wi, const Vector& wo) const = 0;
};

#endif