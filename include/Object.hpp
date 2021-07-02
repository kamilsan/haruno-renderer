#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "Vector.hpp"

class Ray;
class Material;

struct SurfaceInfo {
  SurfaceInfo(const Vector& normal, float u, float v) : normal(normal), uv(std::make_pair(u, v)) {}

  Vector normal;
  std::pair<float, float> uv;
};

class Object {
 public:
  Object(std::shared_ptr<Material> material) : material_(material) {}

  virtual float intersects(const Ray& ray) const = 0;
  virtual SurfaceInfo getSurfaceInfo(const Vector& position) const = 0;

  const Material& getMaterial() const { return *material_; }

 private:
  std::shared_ptr<Material> material_;
};

#endif