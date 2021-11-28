#ifndef CHECKERBOARD_TEXTURE_HPP
#define CHECKERBOARD_TEXTURE_HPP

#include <cmath>

#include "BaseTexture.hpp"

class CheckerboardTexture : public BaseTexture {
 public:
  CheckerboardTexture(float sizeU, float sizeV) : sizeU_(sizeU), sizeV_(sizeV) {}

  Color get(const Vector2f& uv) const override {
    const auto uScaled = sizeU_ * uv.x;
    const auto vScaled = sizeV_ * uv.y;
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