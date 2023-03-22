#ifndef REINHARD_MAPPER_HPP
#define REINHARD_MAPPER_HPP

#include <optional>

#include "Color.hpp"
#include "Math.hpp"
#include "ToneMapper.hpp"

class ReinhardMapper : public ToneMapper {
 public:
  ReinhardMapper(float keyValue = 0.18f, bool useLWhite = false, std::optional<float> Lwhite = {})
      : keyValue_(keyValue), useLWhite_(useLWhite), Lwhite_(Lwhite) {}

  Image apply(const Image& input) const override;

 private:
  static Vector3f RGBToXYZ(const Color& color);
  static Color XYZToRGB(const Vector3f& color);

  float keyValue_;
  bool useLWhite_;
  std::optional<float> Lwhite_;
};

#endif  // REINHARD_MAPPER_HPP