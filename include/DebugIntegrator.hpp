#ifndef DEBUG_INTEGRATOR_HPP
#define DEBUG_INTEGRATOR_HPP

#include "Integrator.hpp"

class DebugIntegrator : public Integrator {
 public:
  enum class OutputType { Albedo, Normal, Depth };

  DebugIntegrator(const OutputType& outputType) : outputType_(outputType) {}

  Color integrate(const Ray& cameraRay, const Scene& scene, RNG& rng) const override;

 private:
  OutputType outputType_;
};

#endif  // DEBUG_INTEGRATOR_HPP