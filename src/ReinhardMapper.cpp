#include "ReinhardMapper.hpp"

#include "Image.hpp"

Vector3f ReinhardMapper::RGBToXYZ(const Color& color) {
  Vector3f result;

  result.x = 0.4124f * color.r + 0.3576f * color.g + 0.1805f * color.b;
  result.y = 0.2126f * color.r + 0.7152f * color.g + 0.0722f * color.b;
  result.z = 0.0193f * color.r + 0.1192f * color.g + 0.9505f * color.b;

  return result;
}

Color ReinhardMapper::XYZToRGB(const Vector3f& color) {
  Color result;

  result.r = 3.2406f * color.x - 1.5372f * color.y - 0.4986f * color.z;
  result.g = -0.9689f * color.x + 1.8758f * color.y + 0.0415f * color.z;
  result.b = 0.0557f * color.x - 0.2040f * color.y + 1.0570f * color.z;

  return result;
}

Image ReinhardMapper::apply(const Image& input) const {
  Image imageXYZ = input;

  const auto N = input.getWidth() * input.getHeight();
  float Lavg = 0.0f;
  float Lmax = 0.0f;

  for (unsigned int y = 0; y < input.getHeight(); ++y) {
    for (unsigned int x = 0; x < input.getWidth(); ++x) {
      const auto colorRGB = input.getPixel(x, y);
      auto colorXYZ = RGBToXYZ(colorRGB);

      const auto L = colorXYZ.y;
      Lmax = std::max(Lmax, L);
      Lavg += std::log(L + 0.00001f);

      // Convert to xyY
      const auto factor = 1.0f / (colorXYZ.x + colorXYZ.y + colorXYZ.z);
      colorXYZ *= factor;
      colorXYZ.z = L;

      imageXYZ.setPixel(x, y, Color(colorXYZ.x, colorXYZ.y, colorXYZ.z));
    }
  }

  Lavg = std::exp(Lavg / N);

  const float Lwhite = Lwhite_.value_or(Lmax);

  Image output = input;

  for (unsigned int y = 0; y < input.getHeight(); ++y) {
    for (unsigned int x = 0; x < input.getWidth(); ++x) {
      const auto colorXYZ = imageXYZ.getPixel(x, y);
      const auto L = colorXYZ.b * keyValue_ / Lavg;

      float Lfinal = 1.0f;

      if (useLWhite_) {
        Lfinal = (L * (1.0f + L / (Lwhite * Lwhite))) / (1.0f + L);
      } else {
        Lfinal = L / (1.0f + L);
      }

      const float X = Lfinal / colorXYZ.g * colorXYZ.r;
      const float Y = Lfinal;
      const float Z = Lfinal / colorXYZ.g * (1.0f - colorXYZ.r - colorXYZ.g);

      const auto colorRemapped = XYZToRGB(Vector3f(X, Y, Z));
      output.setPixel(x, y, colorRemapped);
    }
  }

  return output;
}