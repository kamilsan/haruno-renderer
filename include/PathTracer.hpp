#ifndef PATH_TRACER_HPP
#define PATH_TRACER_HPP

#include "Integrator.hpp"

class PathTracer : public Integrator {
 public:
  Color integrate(const Ray& cameraRay, const Scene& scene, RNG& rng) override;

 private:
};

#endif  // PATH_TRACER_HPP