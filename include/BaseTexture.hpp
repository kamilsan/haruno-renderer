#ifndef BASE_TEXTURE_HPP
#define BASE_TEXTURE_HPP

#include "Color.hpp"

class BaseTexture {
 public:
  virtual ~BaseTexture(){};

  virtual Color get(float u, float v) const = 0;
};

#endif