#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <memory>
#include <optional>

#include "Color.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"

class Ray;
class Material;
class RNG;
class Light;

struct SurfaceInfo {
  SurfaceInfo() = default;
  SurfaceInfo(const Vector3t& normal, const Vector2t& uv) : normal(normal), uv(uv), emittance() {}
  SurfaceInfo(const Vector3t& normal, const Vector2t& uv, const Color& emittance)
      : normal(normal), uv(uv), emittance(emittance) {}

  Vector3t normal;
  Vector2t uv;
  std::optional<Color> emittance;
};

class Object {
 public:
  Object(std::shared_ptr<Material> material) : material_(material), light_() {}

  virtual Float intersects(const Ray& ray, SurfaceInfo& surfaceInfo) const = 0;
  virtual Vector3t sample(RNG& rng, SurfaceInfo& surfaceInfo, Float& pdf) const = 0;

  void setLight(std::weak_ptr<Light> light) { light_ = light; }

  const Material& getMaterial() const { return *material_; }
  std::weak_ptr<Light> getLight() { return light_; }

 private:
  std::shared_ptr<Material> material_;
  std::weak_ptr<Light> light_;
};

#endif