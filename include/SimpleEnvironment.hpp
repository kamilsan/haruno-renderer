#ifndef SIMPLE_ENVIRONMENT_HPP
#define SIMPLE_ENVIRONMENT_HPP

#include "Color.hpp"
#include "Environment.hpp"
#include "Vector3.hpp"

class SimpleEnvironment : public Environment {
 public:
  SimpleEnvironment(const Color& zenithColor, const Color& horizonColor, const Color& groundColor)
      : zenithColor_(zenithColor), horizonColor_(horizonColor), groundColor_(groundColor) {}

  Color getColor(const Vector3f& direction, float maxT = -1.0f) const override;
  Color getTransmittance(const Ray&, float) const override { return Color{1.0f}; }

 private:
  Color zenithColor_;
  Color horizonColor_;
  Color groundColor_;
};

#endif