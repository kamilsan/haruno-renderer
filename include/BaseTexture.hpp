#ifndef BASE_TEXTURE_HPP
#define BASE_TEXTURE_HPP

#include "Color.hpp"
#include "Types.hpp"
#include "Vector2.hpp"

class BaseTexture {
 public:
  virtual ~BaseTexture() = default;

  virtual Color get(const Vector2t& uv) const = 0;
};

#endif