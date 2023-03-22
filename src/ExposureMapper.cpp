#include "ExposureMapper.hpp"

#include "Image.hpp"
#include "Math.hpp"

ExposureMapper::ExposureMapper(float exposure) : gain_(std::exp2f(exposure)) {}

Image ExposureMapper::apply(const Image& input) const {
  Image output = input;

  for (unsigned int y = 0; y < input.getHeight(); ++y) {
    for (unsigned int x = 0; x < input.getWidth(); ++x) {
      const auto sourceValue = input.getPixel(x, y);
      const auto newValue = sourceValue * gain_;
      output.setPixel(x, y, newValue);
    }
  }

  return output;
}