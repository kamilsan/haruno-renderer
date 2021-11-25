#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <memory>
#include <vector>

#include "Color.hpp"
#include "Math.hpp"

class Image {
 public:
  Image(const std::string& filename);
  Image(unsigned int width, unsigned int height);

  Image(const Image& other);
  Image(Image&& other);

  bool save(const std::string& filename, const bool gammaCompress = true) const;

  void clear(const Color& color);

  unsigned int getWidth() const { return width_; }
  unsigned int getHeight() const { return height_; }

  inline Color getPixel(unsigned int x, unsigned int y) const;
  inline void setPixel(unsigned int x, unsigned int y, const Color& color);

  Image& operator=(const Image& other);
  Image& operator=(Image&& other);

  float operator[](unsigned int index) const { return pixels_[index]; }
  float& operator[](unsigned int index) { return pixels_[index]; }

 private:
  inline float sRGBEncode(float c) const;
  inline float sRGBDecode(float c) const;

  unsigned int width_;
  unsigned int height_;
  unsigned int len_;
  std::unique_ptr<float[]> pixels_;
};

Color Image::getPixel(unsigned int x, unsigned int y) const {
  const int index = 3 * (y * width_ + x);

  Color c;
  c.r = pixels_[index];
  c.g = pixels_[index + 1];
  c.b = pixels_[index + 2];

  return c;
}

void Image::setPixel(unsigned int x, unsigned int y, const Color& color) {
  const int index = 3 * (y * width_ + x);

  pixels_[index] = color.r;
  pixels_[index + 1] = color.g;
  pixels_[index + 2] = color.b;
}

float Image::sRGBEncode(float c) const {
  const float y = 1.0f / 2.4f;

  if (c <= 0.0031308f)
    return c * 12.92f;
  else
    return 1.055f * std::pow(c, y) - 0.055f;
}

float Image::sRGBDecode(float c) const {
  if (c <= 0.04045f)
    return c / 12.92f;
  else
    return std::pow((c + 0.055f) / 1.055f, 2.4f);
}

#endif