#ifndef BASE_TEXTURE_HPP
#define BASE_TEXTURE_HPP

#include "Color.hpp"
#include "Vector2.hpp"

class BaseTexture {
 public:
  virtual ~BaseTexture(){};

  virtual Color get(const Vector2f& uv) const = 0;
};

#endif