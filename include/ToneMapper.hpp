#ifndef TONE_MAPPER_HPP
#define TONE_MAPPER_HPP

class Image;

class ToneMapper {
 public:
  virtual ~ToneMapper() = default;
  virtual Image apply(const Image&) const = 0;
};

#endif  // TONE_MAPPER_HPP