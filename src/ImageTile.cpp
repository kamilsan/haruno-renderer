#include "ImageTile.hpp"

#include <cstring>
#include <fstream>

ImageTile::ImageTile(unsigned int minX, unsigned int maxX, unsigned int minY, unsigned int maxY):
  minX_(minX), maxX_(maxX), minY_(minY), maxY_(maxY)
{
  if(maxX < minX || maxY < minY)
  {
    throw std::runtime_error("Improper ImageTile bounds!");
  }

  width_ = maxX_ - minX_;
  height_ = maxY_ - minY_;
  len_ = 3 * width_ * height_;
  pixels_ = std::make_unique<float[]>(len_);
  memset(pixels_.get(), 0, len_ * sizeof(float));
}

ImageTile::ImageTile(const ImageTile& other)
{
  minX_ = other.minX_;
  maxX_ = other.maxX_;
  minY_ = other.minY_;
  maxY_ = other.maxY_;
  width_ = other.width_;
  height_ = other.height_;
  len_ = other.len_;

  pixels_ = std::make_unique<float[]>(len_);
  memcpy(pixels_.get(), other.pixels_.get(), len_ * sizeof(float));
}

ImageTile::ImageTile(ImageTile&& other)
{
  minX_ = other.minX_;
  maxX_ = other.maxX_;
  minY_ = other.minY_;
  maxY_ = other.maxY_;
  width_ = other.width_;
  height_ = other.height_;
  len_ = other.len_;
  pixels_ = std::move(other.pixels_);
}

ImageTile& ImageTile::operator=(const ImageTile& other)
{
  if(&other != this)
  {
    minX_ = other.minX_;
    maxX_ = other.maxX_;
    minY_ = other.minY_;
    maxY_ = other.maxY_;
    width_ = other.width_;
    height_ = other.height_;
    len_ = other.len_;

    pixels_ = std::make_unique<float[]>(len_);
    memcpy(pixels_.get(), other.pixels_.get(), len_ * sizeof(float));
  }

  return *this;
}

ImageTile& ImageTile::operator=(ImageTile&& other)
{
  if(&other != this)
  {
    minX_ = other.minX_;
    maxX_ = other.maxX_;
    minY_ = other.minY_;
    maxY_ = other.maxY_;
    width_ = other.width_;
    height_ = other.height_;
    len_ = other.len_;
    pixels_ = std::move(other.pixels_);
  }

  return *this;
}

void ImageTile::clear(const Color& color)
{
  for(unsigned int i = 0; i < len_;)
  {
    pixels_[i++] = color.r;
    pixels_[i++] = color.g;
    pixels_[i++] = color.b;
  }
}
