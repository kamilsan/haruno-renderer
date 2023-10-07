#ifndef RANDOM_WALK_HPP
#define RANDOM_WALK_HPP

#include "Integrator.hpp"

class RandomWalk : public Integrator {
 public:
  Color integrate(const Ray& cameraRay, const Scene& scene, RNG& rng) const override;

 private:
};

#endif  // RANDOM_WALK_HPP