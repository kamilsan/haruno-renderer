#ifndef AREA_LIGHT_HPP
#define AREA_LIGHT_HPP

#include <memory>

#include "Color.hpp"
#include "Light.hpp"
#include "Object.hpp"
#include "RNG.hpp"

class AreaLight : public Light {
 public:
  AreaLight(std::shared_ptr<Object> object, const Color& emittance)
      : object_(std::move(object)), emittance_(emittance) {}

  std::shared_ptr<Object> getObject() override { return object_; }

  Color evaluate(const Vector3f&) const override { return emittance_; }
  Ray getShadowRay(const Vector3f&, float&) const override { return Ray{{}, {}}; }
  bool isDelta() const override { return false; }
  Color sampleLe(Vector3f& position, SurfaceInfo& surfaceInfo, RNG& rng,
                 float& pdf) const override {
    position = object_->sample(rng, surfaceInfo, pdf);
    return emittance_;
  }
  float intersects(const Ray& ray, SurfaceInfo& surfaceInfo) const {
    return object_->intersects(ray, surfaceInfo);
  }

 private:
  std::shared_ptr<Object> object_;
  Color emittance_;
};

#endif