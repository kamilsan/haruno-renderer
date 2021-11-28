#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <memory>

#include "Vector2.hpp"
#include "Vector3.hpp"

class Ray;
class Material;

struct SurfaceInfo {
  SurfaceInfo() = default;
  SurfaceInfo(const Vector3f& normal, const Vector2f& uv) : normal(normal), uv(uv) {}

  Vector3f normal;
  Vector2f uv;
};

class Object {
 public:
  Object(std::shared_ptr<Material> material) : material_(material) {}

  virtual float intersects(const Ray& ray, SurfaceInfo& surfaceInfo) const = 0;

  const Material& getMaterial() const { return *material_; }

 private:
  std::shared_ptr<Material> material_;
};

#endif