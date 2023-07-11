#ifndef EXPOSURE_MAPPER_HPP
#define EXPOSURE_MAPPER_HPP

#include "ToneMapper.hpp"
#include "Types.hpp"

class ExposureMapper : public ToneMapper {
 public:
  ExposureMapper(Float exposure);

  Image apply(const Image&) const override;

 private:
  Float gain_;
};

#endif  // EXPOSURE_MAPPER_HPP