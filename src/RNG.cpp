#include "RNG.hpp"

#include "Math.hpp"

RNG::RNG() : distribution_(0.0f, 1.0f) {
  const auto seed = std::chrono::steady_clock::now().time_since_epoch().count();
  engine_ = std::mt19937(seed);
}

RNG::RNG(unsigned long seed) : distribution_(0.0f, 1.0f) { engine_ = std::mt19937(seed); }

RNG RNG::createChild(unsigned int id) {
  const auto randomValue = engine_();
  const auto newSeed = randomValue + id;
  return RNG(newSeed);
}

Vector3f RNG::sampleCircle() {
  const float r = std::sqrt(distribution_(engine_));
  const float theta = TAU * distribution_(engine_);

  const float x = r * std::cos(theta);
  const float y = r * std::sin(theta);

  return Vector3f{x, y, 0};
}

Vector3f RNG::sampleHemisphereUniform() {
  const float cosTheta = distribution_(engine_);
  const float sinTheta = std::sqrt(1.0f - cosTheta * cosTheta);

  float phi = TAU * distribution_(engine_);

  return Vector3f(sinTheta * std::cos(phi), cosTheta, sinTheta * std::sin(phi));
}

Vector3f RNG::sampleHemisphereCosineWeighted() {
  const float sinTheta = std::sqrt(distribution_(engine_));
  const float cosTheta = std::sqrt(1.0f - sinTheta * sinTheta);

  float phi = TAU * distribution_(engine_);

  return Vector3f(sinTheta * std::cos(phi), cosTheta, sinTheta * std::sin(phi));
}