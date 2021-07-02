#ifndef IMAGE_TILE_HPP
#define IMAGE_TILE_HPP

#include <memory>
#include <vector>

#include "Color.hpp"

class ImageTile {
 public:
  ImageTile(unsigned int minX, unsigned int maxX, unsigned int minY, unsigned int maxY);

  ImageTile(const ImageTile& other);
  ImageTile(ImageTile&& other);

  void clear(const Color& color);

  unsigned int getMinX() const { return minX_; }
  unsigned int getMaxX() const { return maxX_; }
  unsigned int getMinY() const { return minY_; }
  unsigned int getMaxY() const { return maxY_; }

  unsigned int getWidth() const { return width_; }
  unsigned int getHeight() const { return height_; }

  inline Color getPixel(unsigned int x, unsigned int y) const;
  inline void setPixel(unsigned int x, unsigned int y, const Color& color);

  ImageTile& operator=(const ImageTile& other);
  ImageTile& operator=(ImageTile&& other);

  float operator[](unsigned int index) const { return pixels_[index]; }
  float& operator[](unsigned int index) { return pixels_[index]; }

 private:
  unsigned int minX_;
  unsigned int maxX_;
  unsigned int minY_;
  unsigned int maxY_;
  unsigned int width_;
  unsigned int height_;
  unsigned int len_;
  std::unique_ptr<float[]> pixels_;
};

Color ImageTile::getPixel(unsigned int x, unsigned int y) const {
  const int index = 3 * (y * width_ + x);

  Color c;
  c.r = pixels_[index];
  c.g = pixels_[index + 1];
  c.b = pixels_[index + 2];

  return c;
}

void ImageTile::setPixel(unsigned int x, unsigned int y, const Color& color) {
  const int index = 3 * (y * width_ + x);

  pixels_[index] = color.r;
  pixels_[index + 1] = color.g;
  pixels_[index + 2] = color.b;
}

#endif