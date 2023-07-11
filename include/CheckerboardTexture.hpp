#ifndef CHECKERBOARD_TEXTURE_HPP
#define CHECKERBOARD_TEXTURE_HPP

#include <cmath>

#include "BaseTexture.hpp"

class CheckerboardTexture : public BaseTexture {
 public:
  CheckerboardTexture(Float sizeU, Float sizeV) : sizeU_(sizeU), sizeV_(sizeV) {}

  Color get(const Vector2t& uv) const override {
    const auto uScaled = sizeU_ * uv.x;
    const auto vScaled = sizeV_ * uv.y;
    const auto uMod = uScaled - std::floor(uScaled);
    const auto vMod = vScaled - std::floor(vScaled);

    const auto value = (uMod < 0.5) ^ (vMod < 0.5);
    return Color{value * static_cast<Float>(1.0)};
  }

 private:
  Float sizeU_;
  Float sizeV_;
};

#endif