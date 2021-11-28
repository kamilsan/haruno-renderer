#ifndef PLANE_HPP
#define PLANE_HPP

#include <memory>

#include "Material.hpp"
#include "Object.hpp"
#include "Ray.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"

class Plane : public Object {
 public:
  Plane(const Vector3f& point, const Vector3f& normal, const Vector3f& tangent,
        const Vector3f& bitangent, std::shared_ptr<Material> material)
      : Object(material), point_(point) {
    normal_ = normal.normalized();
    tangent_ = (tangent - tangent.dot(normal_) * normal_).normalized();
    bitangent_ = (bitangent - bitangent.dot(normal_) * normal_ - bitangent.dot(tangent_) * tangent_)
                     .normalized();
  }

  const Vector3f& getPoint() const { return point_; }
  const Vector3f& getNormal() const { return normal_; }

  inline float intersects(const Ray& ray, SurfaceInfo& surfaceInfo) const override;

 private:
  Vector3f point_;
  Vector3f normal_;
  Vector3f tangent_;
  Vector3f bitangent_;
};

float Plane::intersects(const Ray& ray, SurfaceInfo& surfaceInfo) const {
  const float don = ray.getDirection().dot(normal_);
  if (don > -EPSILON && don < EPSILON) {
    return -1;
  }

  const auto t = (point_ - ray.getOrigin()).dot(normal_) / don;
  if (t < 0.0f) {
    return -1;
  }

  const auto fromPlanePoint = ray(t) - point_;
  const float u = fromPlanePoint.dot(tangent_);
  const float v = fromPlanePoint.dot(bitangent_);

  surfaceInfo.normal = normal_;
  surfaceInfo.uv = Vector2f(u, v);

  return t;
}

#endif
