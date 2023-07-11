#include "RNG.hpp"

#include "Math.hpp"

RNG::RNG() : distribution_(0.0, 1.0) {
  const auto seed = std::chrono::steady_clock::now().time_since_epoch().count();
  engine_ = std::mt19937(seed);
}

RNG::RNG(unsigned long seed) : distribution_(0.0, 1.0) { engine_ = std::mt19937(seed); }

RNG RNG::createChild(unsigned int id) {
  const auto randomValue = engine_();
  const auto newSeed = randomValue + id;
  return RNG(newSeed);
}

Vector3t RNG::sampleCircle() {
  const Float r = std::sqrt(distribution_(engine_));
  const Float theta = TAU * distribution_(engine_);

  const Float x = r * std::cos(theta);
  const Float y = r * std::sin(theta);

  return Vector3t{x, y, 0};
}

Vector3t RNG::sampleHemisphereUniform() {
  const Float cosTheta = distribution_(engine_);
  const Float sinTheta = std::sqrt(1.0 - cosTheta * cosTheta);

  Float phi = TAU * distribution_(engine_);

  return Vector3t(sinTheta * std::cos(phi), cosTheta, sinTheta * std::sin(phi));
}

Vector3t RNG::sampleHemisphereCosineWeighted() {
  const Float sinTheta = std::sqrt(distribution_(engine_));
  const Float cosTheta = std::sqrt(1.0 - sinTheta * sinTheta);

  Float phi = TAU * distribution_(engine_);

  return Vector3t(sinTheta * std::cos(phi), cosTheta, sinTheta * std::sin(phi));
}