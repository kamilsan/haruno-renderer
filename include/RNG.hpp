#ifndef RNG_HPP
#define RNG_HPP

#include <chrono>
#include <random>

class RNG
{
public:
  RNG(): distribution_(0.0f, 1.0f)
  {
    const auto seed = std::chrono::steady_clock::now().time_since_epoch().count();
    engine_ = std::mt19937(seed);
  }

  inline float get();

private:
  std::mt19937 engine_;
  std::uniform_real_distribution<float> distribution_;
};


float RNG::get()
{
  return distribution_(engine_);
}

#endif