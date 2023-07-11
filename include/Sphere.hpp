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
  Sphere(const Vector3t& center, Float radius, std::shared_ptr<Material> material)
      : Object(material), center_(center), radius_(radius) {
    pdf_ = 1.0f / (4.0f * PI * radius * radius);
  }

  const Vector3t& getCenter() const { return center_; }
  Float getRadius() const { return radius_; }

  inline Float intersects(const Ray& ray, SurfaceInfo& surfaceInfo) const override;
  inline Vector3t sample(RNG& rng, SurfaceInfo& surfaceInfo, Float& pdf) const override;

 private:
  Vector3t center_;
  Float radius_;
  Float pdf_;
};

Float Sphere::intersects(const Ray& ray, SurfaceInfo& surfaceInfo) const {
  Vector3t centerToOrigin = ray.getOrigin() - center_;
  const Float a = ray.getDirection().lengthSq();
  const Float b = 2.0 * ray.getDirection().dot(centerToOrigin);
  const Float c = centerToOrigin.dot(centerToOrigin) - radius_ * radius_;

  Float t1, t2;
  if (!solveQuadratic(a, b, c, t1, t2)) {
    return -1.0;
  }

  const Float t = t1 > 0.0 ? t1 : t2;

  if (t < 0.0) {
    return -1.0;
  }

  const auto fromCenter = ray(t) - center_;
  const auto normal = fromCenter / radius_;

  const Float theta = std::acos(std::max(
      static_cast<Float>(-1.0), std::min(static_cast<Float>(1.0), fromCenter.y / radius_)));
  const Float phi = std::atan2(fromCenter.z, fromCenter.x);

  const Float u = 0.5 * phi * ONE_OVER_PI + 0.5;
  const Float v = theta * ONE_OVER_PI;

  surfaceInfo.normal = normal;
  surfaceInfo.uv = Vector2t(u, v);

  if (surfaceInfo.normal.dot(ray.getDirection()) > 0.0) {
    surfaceInfo.normal = -surfaceInfo.normal;
  }

  return t;
}

Vector3t Sphere::sample(RNG& rng, SurfaceInfo& surfaceInfo, Float& pdf) const {
  const Float cosTheta = 2.0 * rng.get() - 1.0;
  const Float sinTheta = std::sqrt(1.0 - cosTheta * cosTheta);
  const Float phi = TAU * rng.get();

  const auto normal =
      Vector3t(sinTheta * cosf(phi), cosTheta, sinTheta * std::sin(phi)).normalized();

  const Float theta =
      std::acos(std::max(static_cast<Float>(-1.0), std::min(static_cast<Float>(1.0), cosTheta)));
  const Float u = 0.5 * phi * ONE_OVER_PI + 0.5;
  const Float v = theta * ONE_OVER_PI;

  surfaceInfo.normal = normal;
  surfaceInfo.uv = Vector2t(u, v);

  pdf = pdf_;

  return center_ + radius_ * normal;
}

#endif