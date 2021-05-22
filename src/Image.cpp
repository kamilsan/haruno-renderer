#include "Image.hpp"

#include <cstring>
#include <fstream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Image::Image(const char* filename)
{
  int components = 0;
  unsigned char* data = stbi_load(filename, &width_, &height_, &components, 0);

  if(!data)
  {
    throw std::runtime_error("Could not load provided image file!\n");
  }

  if(components != 3)
  {
    stbi_image_free(data);
    throw std::runtime_error("Unsupported image type!\n");
  }

  len_ = 3*width_*height_;
  pixels_ = std::make_unique<float[]>(len_);

  for(int i = 0; i < len_; ++i)
  {
    pixels_[i] = sRGBDecode(data[i] / 255.0f);
  }
}

Image::Image(int width, int height): width_(width), height_(height)
{
  len_ = 3*width*height;
  pixels_ = std::make_unique<float[]>(len_);
  memset(pixels_.get(), 0, len_ * sizeof(float));
}

Image::Image(const Image& other)
{
  width_ = other.width_;
  height_ = other.height_;
  len_ = other.len_;

  pixels_ = std::make_unique<float[]>(len_);
  memcpy(pixels_.get(), other.pixels_.get(), len_ * sizeof(float));
}

Image::Image(Image&& other)
{
  width_ = other.width_;
  height_ = other.height_;
  len_ = other.len_;
  pixels_ = std::move(other.pixels_);
}

bool Image::save(const char* filename) const
{
  std::ofstream file;
  file.open(filename, std::ios::binary);
  if(!file.is_open()) return false;

  auto data = std::make_unique<unsigned char[]>(len_);
  for(int i = 0; i < len_; ++i)
  {
    const float encoded = sRGBEncode(pixels_[i]);
    data[i] = std::min(255.0f, std::max(0.0f, 255.0f * encoded));
  }

  file << "P6\n" << width_ << " " << height_ << "\n255\n";
  file.write(reinterpret_cast<char*>(data.get()), len_);

  file.close();
  return true;
}

Image& Image::operator=(const Image& other)
{
  if(&other != this)
  {
    width_ = other.width_;
    height_ = other.height_;
    len_ = other.len_;

    pixels_ = std::make_unique<float[]>(len_);
    memcpy(pixels_.get(), other.pixels_.get(), len_ * sizeof(float));
  }

  return *this;
}

Image& Image::operator=(Image&& other)
{
  if(&other != this)
  {
    width_ = other.width_;
    height_ = other.height_;
    len_ = other.len_;
    pixels_ = std::move(other.pixels_);
  }

  return *this;
}

void Image::clear(const Color& color)
{
  for(int i = 0; i < len_;)
  {
    pixels_[i++] = color.r;
    pixels_[i++] = color.g;
    pixels_[i++] = color.b;
  }
}
