#ifndef AREA_LIGHT_HPP
#define AREA_LIGHT_HPP

#include <memory>

#include "Color.hpp"
#include "Light.hpp"
#include "Object.hpp"
#include "RNG.hpp"
#include "Types.hpp"

class AreaLight : public Light {
 public:
  AreaLight(std::shared_ptr<Object> object, const Color& emittance)
      : object_(std::move(object)), emittance_(emittance) {}

  std::shared_ptr<Object> getObject() override { return object_; }

  Color evaluate(const Vector3t&) const override { return emittance_; }
  Ray getShadowRay(const Vector3t&, Float&) const override { return Ray{{}, {}}; }
  bool isDelta() const override { return false; }
  Color sampleLe(Vector3t& position, SurfaceInfo& surfaceInfo, RNG& rng,
                 Float& pdf) const override {
    position = object_->sample(rng, surfaceInfo, pdf);
    return emittance_;
  }

 private:
  std::shared_ptr<Object> object_;
  Color emittance_;
};

#endif