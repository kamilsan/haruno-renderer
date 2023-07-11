#include "ReinhardMapper.hpp"

#include "Image.hpp"

Vector3t ReinhardMapper::RGBToXYZ(const Color& color) {
  Vector3t result;

  result.x = 0.4124 * color.r + 0.3576 * color.g + 0.1805 * color.b;
  result.y = 0.2126 * color.r + 0.7152 * color.g + 0.0722 * color.b;
  result.z = 0.0193 * color.r + 0.1192 * color.g + 0.9505 * color.b;

  return result;
}

Color ReinhardMapper::XYZToRGB(const Vector3t& color) {
  Color result;

  result.r = 3.2406 * color.x - 1.5372 * color.y - 0.4986 * color.z;
  result.g = -0.9689 * color.x + 1.8758 * color.y + 0.0415 * color.z;
  result.b = 0.0557 * color.x - 0.2040 * color.y + 1.0570 * color.z;

  return result;
}

Image ReinhardMapper::apply(const Image& input) const {
  Image imageXYZ = input;

  const auto N = input.getWidth() * input.getHeight();
  Float Lavg = 0.0;
  Float Lmax = 0.0;

  for (unsigned int y = 0; y < input.getHeight(); ++y) {
    for (unsigned int x = 0; x < input.getWidth(); ++x) {
      const auto colorRGB = input.getPixel(x, y);
      auto colorXYZ = RGBToXYZ(colorRGB);

      const auto L = colorXYZ.y;
      Lmax = std::max(Lmax, L);
      Lavg += std::log(L + 0.00001);

      // Convert to xyY
      const auto factor = 1.0 / (colorXYZ.x + colorXYZ.y + colorXYZ.z);
      colorXYZ *= factor;
      colorXYZ.z = L;

      imageXYZ.setPixel(x, y, Color(colorXYZ.x, colorXYZ.y, colorXYZ.z));
    }
  }

  Lavg = std::exp(Lavg / N);

  const Float Lwhite = Lwhite_.value_or(Lmax);

  Image output = input;

  for (unsigned int y = 0; y < input.getHeight(); ++y) {
    for (unsigned int x = 0; x < input.getWidth(); ++x) {
      const auto colorXYZ = imageXYZ.getPixel(x, y);
      const auto L = colorXYZ.b * keyValue_ / Lavg;

      Float Lfinal = 1.0;

      if (useLWhite_) {
        Lfinal = (L * (1.0 + L / (Lwhite * Lwhite))) / (1.0 + L);
      } else {
        Lfinal = L / (1.0 + L);
      }

      const Float X = Lfinal / colorXYZ.g * colorXYZ.r;
      const Float Y = Lfinal;
      const Float Z = Lfinal / colorXYZ.g * (1.0 - colorXYZ.r - colorXYZ.g);

      const auto colorRemapped = XYZToRGB(Vector3t(X, Y, Z));
      output.setPixel(x, y, colorRemapped);
    }
  }

  return output;
}