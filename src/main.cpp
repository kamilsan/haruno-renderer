#include "Image.hpp"

int main()
{
  Image img{1920, 1080};

  for(int y = 0; y < img.getHeight(); ++y)
  {
    for(int x = 0; x < img.getWidth(); ++x)
    {
      const float v = y / (img.getHeight() - 1.0f);
      img.setPixel(x, y, Color{v});
    }
  }

  img.save("result.ppm");

  return 0;
}