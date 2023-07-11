#ifndef SOLID_TEXTURE_HPP
#define SOLID_TEXTURE_HPP

#include "BaseTexture.hpp"

class SolidTexture : public BaseTexture {
 public:
  SolidTexture(const Color& color) : color_(color) {}

  Color get(const Vector2t&) const override { return color_; }

 private:
  Color color_;
};

#endif