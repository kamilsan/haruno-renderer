#ifndef REINHARD_MAPPER_HPP
#define REINHARD_MAPPER_HPP

#include <optional>

#include "Color.hpp"
#include "Math.hpp"
#include "ToneMapper.hpp"

class ReinhardMapper : public ToneMapper {
 public:
  ReinhardMapper(Float keyValue = 0.18, bool useLWhite = false, std::optional<Float> Lwhite = {})
      : keyValue_(keyValue), useLWhite_(useLWhite), Lwhite_(Lwhite) {}

  Image apply(const Image& input) const override;

 private:
  static Vector3t RGBToXYZ(const Color& color);
  static Color XYZToRGB(const Vector3t& color);

  Float keyValue_;
  bool useLWhite_;
  std::optional<Float> Lwhite_;
};

#endif  // REINHARD_MAPPER_HPP