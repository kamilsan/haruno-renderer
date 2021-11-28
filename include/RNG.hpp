#ifndef RNG_HPP
#define RNG_HPP

#include <chrono>
#include <random>

#include "Vector3.hpp"

class RNG {
 public:
  RNG();
  explicit RNG(unsigned long seed);

  RNG createChild(unsigned int id);

  inline float get();
  Vector3f sampleCircle();

 private:
  std::mt19937 engine_;
  std::uniform_real_distribution<float> distribution_;
};

float RNG::get() { return distribution_(engine_); }

#endif