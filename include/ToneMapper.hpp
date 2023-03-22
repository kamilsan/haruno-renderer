#ifndef TONE_MAPPER_H
#define TONE_MAPPER_H

class Image;

class ToneMapper {
 public:
  virtual ~ToneMapper() = default;
  virtual Image apply(const Image&) const = 0;
};

#endif  // TONE_MAPPER_H