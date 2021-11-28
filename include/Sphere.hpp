#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Material.hpp"
#include "Math.hpp"
#include "Object.hpp"
#include "Ray.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"

class Sphere : public Object {
 public:
  Sphere(const Vector3f& center, float radius, std::shared_ptr<Material> material)
      : Object(material), center_(center), radius_(radius) {}

  const Vector3f& getCenter() const { return center_; }
  float getRadius() const { return radius_; }

  inline float intersects(const Ray& ray, SurfaceInfo& surfaceInfo) const override;

 private:
  Vector3f center_;
  float radius_;
};

// NOTE: Ray direction is assumed to be normalized
float Sphere::intersects(const Ray& ray, SurfaceInfo& surfaceInfo) const {
  Vector3f centerToOrigin = ray.getOrigin() - center_;
  const float b = 2.0f * ray.getDirection().dot(centerToOrigin);
  const float c = centerToOrigin.dot(centerToOrigin) - radius_ * radius_;
  float delta = b * b - 4.0f * c;

  if (delta < 0.0f) {
    return -1.0f;
  }

  delta = std::sqrt(delta);

  const float q = -0.5f * (b + std::copysign(1.0f, b) * delta);

  const float t1 = q;
  const float t2 = c / q;
  const float t = std::min(t1, t2);

  if (t < 0.0f) {
    return -1.0f;
  }

  const auto fromCenter = ray(t) - center_;
  const auto normal = fromCenter / radius_;

  const float theta = std::acos(std::max(-1.0f, std::min(1.0f, fromCenter.y / radius_)));
  const float phi = std::atan2(fromCenter.z, fromCenter.x);

  const float u = 0.5f * phi * ONE_OVER_PI + 0.5f;
  const float v = theta * ONE_OVER_PI;

  surfaceInfo.normal = normal;
  surfaceInfo.uv = Vector2f(u, v);

  return t;
}

#endif