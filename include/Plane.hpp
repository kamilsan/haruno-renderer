#ifndef PLANE_HPP
#define PLANE_HPP

#include <memory>

#include "Material.hpp"
#include "Object.hpp"
#include "Ray.hpp"
#include "Vector.hpp"

class Plane : public Object {
 public:
  Plane(const Vector& point, const Vector& normal, const Vector& tangent, const Vector& bitangent,
        std::shared_ptr<Material> material)
      : Object(material), point_(point) {
    normal_ = normal.normalized();
    tangent_ = (tangent - tangent.dot(normal_) * normal_).normalized();
    bitangent_ = (bitangent - bitangent.dot(normal_) * normal_ - bitangent.dot(tangent_) * tangent_)
                     .normalized();
  }

  const Vector& getPoint() const { return point_; }
  const Vector& getNormal() const { return normal_; }

  inline float intersects(const Ray& ray) const override;
  inline SurfaceInfo getSurfaceInfo(const Vector& position) const override;

 private:
  Vector point_;
  Vector normal_;
  Vector tangent_;
  Vector bitangent_;
};

float Plane::intersects(const Ray& ray) const {
  const float don = ray.getDirection().dot(normal_);
  if (don > -0.00001f && don < 0.00001f) return -1;

  return -(ray.getOrigin() - point_).dot(normal_) / don;
}

SurfaceInfo Plane::getSurfaceInfo(const Vector& position) const {
  const auto fromPlanePoint = position - point_;

  const float u = fromPlanePoint.dot(tangent_);
  const float v = fromPlanePoint.dot(bitangent_);

  return SurfaceInfo{normal_, u, v};
}

#endif
