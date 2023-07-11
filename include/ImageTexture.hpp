#ifndef IMAGE_TEXTURE_HPP
#define IMAGE_TEXTURE_HPP

#include <cmath>

#include "BaseTexture.hpp"
#include "Image.hpp"

class ImageTexture : public BaseTexture {
 public:
  ImageTexture(const std::string& imagePath) : image_(imagePath.c_str()) {}

  Color get(const Vector2t& uv) const {
    const auto uRepeat = uv.x - std::floor(uv.x);
    const auto vRepeat = 1.0 - (uv.y - std::floor(uv.y));

    const unsigned int s = uRepeat * image_.getWidth();
    const unsigned int t = vRepeat * image_.getHeight();

    return image_.getPixel(s, t);
  }

 private:
  Image image_;
};

#endif