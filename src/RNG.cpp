#include "RNG.hpp"

#include "Math.hpp"

RNG::RNG(): distribution_(0.0f, 1.0f)
{
  const auto seed = std::chrono::steady_clock::now().time_since_epoch().count();
  engine_ = std::mt19937(seed);
}

RNG::RNG(unsigned long seed): distribution_(0.0f, 1.0f)
{
  engine_ = std::mt19937(seed);
}

RNG RNG::createChild(unsigned int id)
{
  const auto randomValue = engine_();
  const auto newSeed = randomValue + id;
  return RNG(newSeed);
}

Vector RNG::sampleCircle()
{
  const float r = std::sqrt(distribution_(engine_));
  const float theta = TAU * distribution_(engine_);

  const float x = r * std::cos(theta);
  const float y = r * std::sin(theta);

  return Vector{x, y, 0};
}