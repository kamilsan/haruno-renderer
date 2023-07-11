#ifndef RNG_HPP
#define RNG_HPP

#include <chrono>
#include <random>

#include "Types.hpp"

class RNG {
 public:
  RNG();
  explicit RNG(unsigned long seed);

  RNG createChild(unsigned int id);

  inline Float get();
  Vector3t sampleCircle();
  Vector3t sampleHemisphereUniform();
  Vector3t sampleHemisphereCosineWeighted();

 private:
  std::mt19937 engine_;
  std::uniform_real_distribution<Float> distribution_;
};

Float RNG::get() { return distribution_(engine_); }

#endif