#ifndef AREA_LIGHT_HPP
#define AREA_LIGHT_HPP

#include "Light.hpp"
#include "Object.hpp"
#include "Color.hpp"
#include "RNG.hpp"

#include <memory>

class AreaLight : public Light {
public:
  AreaLight(std::unique_ptr<Object> object, const Color& emittance):
    object_(std::move(object)), emittance_(emittance) {}

  Color evaluate(const Vector3f&) const override { return emittance_; }
  Ray getShadowRay(const Vector3f&, float&) const override { return Ray{{}, {}}; }
  bool isDelta() const override { return false; }
  float pdf() const override { return 1.0f / object_->area(); }
  Color sampleLe(Vector3f& position, RNG& rng) const override { 
    position = object_->sample(rng);
    return emittance_;
  }
  float intersects(const Ray& ray, SurfaceInfo& surfaceInfo) const { return object_->intersects(ray, surfaceInfo); }
private:
  std::unique_ptr<Object> object_;
  Color emittance_;
};

#endif