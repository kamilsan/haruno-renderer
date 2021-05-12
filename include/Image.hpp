#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <cmath>
#include <memory>
#include <vector>
#include <utility>

#include "Color.hpp"

class Image
{
public:
  Image(const char* filename);
  Image(int width, int height);

  Image(const Image& other);
  Image(Image&& other);

  bool save(const char* fileName) const;

  void clear(const Color& color);

  int getWidth() const { return width_; }
  int getHeight() const { return height_; }

  inline Color getPixel(int x, int y) const;
  inline void setPixel(int x, int y, const Color& color);

  Image& operator=(const Image& other);
  Image& operator=(Image&& other);

  float operator[](unsigned int index) const { return pixels_[index]; }
  float& operator[](unsigned int index) { return pixels_[index]; }

private:
  inline float sRGBEncode(float c) const;
  inline float sRGBDecode(float c) const;

  int width_;
  int height_;
  int len_;
  std::unique_ptr<float[]> pixels_;
};

Color Image::getPixel(int x, int y) const
{
  int index = 3*(y*width_ + x);
  
  Color c;
  c.r = pixels_[index];
  c.g = pixels_[index + 1];
  c.b = pixels_[index + 2];
  
  return c;
}

void Image::setPixel(int x, int y, const Color& color)
{
  int index = 3*(y*width_ + x);

  pixels_[index] = color.r;
  pixels_[index + 1] = color.g;
  pixels_[index + 2] = color.b;
}

float Image::sRGBEncode(float c) const
{
  const float y = 1.0f/2.4f;

  if(c <= 0.0031308f) 
    return c * 12.92f;
  else 
    return 1.055f * std::pow(c, y) - 0.055f;

}

float Image::sRGBDecode(float c) const
{
  if(c <= 0.04045f) 
    return c / 12.92f;
  else 
    return std::pow((c+0.055f)/1.055f, 2.4f);
}

#endif