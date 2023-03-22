#ifndef EXPOSURE_MAPPER_HPP
#define EXPOSURE_MAPPER_HPP

#include "ToneMapper.hpp"

class ExposureMapper : public ToneMapper {
 public:
  ExposureMapper(float exposure);

  Image apply(const Image&) const override;

 private:
  float gain_;
};

#endif  // EXPOSURE_MAPPER