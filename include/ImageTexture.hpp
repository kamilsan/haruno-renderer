#ifndef IMAGE_TEXTURE_HPP
#define IMAGE_TEXTURE_HPP

#include <cmath>

#include "BaseTexture.hpp"
#include "Image.hpp"

class ImageTexture : public BaseTexture {
 public:
  ImageTexture(const std::string& imagePath) : image_(imagePath.c_str()) {}

  Color get(float u, float v) const {
    const auto uRepeat = u - std::floor(u);
    const auto vRepeat = 1.0f - (v - std::floor(v));

    const unsigned int s = uRepeat * image_.getWidth();
    const unsigned int t = vRepeat * image_.getHeight();

    return image_.getPixel(s, t);
  }

 private:
  Image image_;
};

#endif