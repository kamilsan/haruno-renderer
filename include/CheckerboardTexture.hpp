#ifndef CHECKERBOARD_TEXTURE_HPP
#define CHECKERBOARD_TEXTURE_HPP

#include "BaseTexture.hpp"

#include <cmath>

class CheckerboardTexture : public BaseTexture
{
public:
  CheckerboardTexture(float sizeU, float sizeV):
    sizeU_(sizeU), sizeV_(sizeV) {}

  Color get(float u, float v) const override
  {
    const auto uScaled = sizeU_ * u;
    const auto vScaled = sizeV_ * v;
    const auto uMod = uScaled - std::floor(uScaled);
    const auto vMod = vScaled - std::floor(vScaled);

    const auto value = (uMod < 0.5f) ^ (vMod < 0.5f);
    return Color{value * 1.0f};
  }

private:
  float sizeU_;
  float sizeV_;
};

#endif