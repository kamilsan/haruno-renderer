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

    const unsigned int s =
        std::max(0u, std::min(static_cast<unsigned int>(uRepeat * (image_.getWidth() - 1)),
                              image_.getWidth() - 1));
    const unsigned int t =
        std::max(0u, std::min(static_cast<unsigned int>(vRepeat * (image_.getHeight() - 1)),
                              image_.getHeight() - 1));

    return image_.getPixel(s, t);
  }

 private:
  Image image_;
};

#endif