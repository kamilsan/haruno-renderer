#ifndef SIMPLE_ENVIRONMENT_HPP
#define SIMPLE_ENVIRONMENT_HPP

#include "Environment.hpp"
#include "Color.hpp"

class Vector;

class SimpleEnvironment : public Environment
{
public:
  SimpleEnvironment(const Color& zenithColor, const Color& horizonColor, const Color& groundColor):
    zenithColor_(zenithColor), horizonColor_(horizonColor), groundColor_(groundColor) {}

  Color getColor(const Vector& direction) const override;

private:
  Color zenithColor_;
  Color horizonColor_;
  Color groundColor_;
};

#endif