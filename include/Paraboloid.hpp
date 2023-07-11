#ifndef PARABOLOID_HPP
#define PARABOLOID_HPP

#include "Material.hpp"
#include "Math.hpp"
#include "Object.hpp"
#include "Ray.hpp"
#include "Transformation.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"

class Paraboloid : public Object {
 public:
  Paraboloid(const Transformation& transformation, Float radius, Float height,
             std::shared_ptr<Material> material)
      : Object(material), transformation_(transformation), radius_(radius), height_(height) {}

  Float getRadius() const { return radius_; }
  Float getHeight() const { return height_; }

  inline Float intersects(const Ray& ray, SurfaceInfo& surfaceInfo) const override;
  inline Vector3t sample(RNG& rng, SurfaceInfo& surfaceInfo, Float& pdf) const override;

 private:
  Transformation transformation_;
  Float radius_;
  Float height_;
};

Float Paraboloid::intersects(const Ray& ray, SurfaceInfo& surfaceInfo) const {
  const auto rayTransformed = transformation_.toObjectCoordinates(ray);

  const auto& origin = rayTransformed.getOrigin();
  const auto& direction = rayTransformed.getDirection();

  auto k = height_ / radius_;
  k = k * k;

  const Float a = k * (direction.x * direction.x + direction.z * direction.z);
  const Float b = 2.0 * k * (origin.x * direction.x + origin.z * direction.z) - direction.y;
  const Float c = k * (origin.x * origin.x + origin.z * origin.z) - origin.y;

  Float t1, t2;
  if (!solveQuadratic(a, b, c, t1, t2)) {
    return -1.0;
  }

  const Float t = t1 > 0.0 ? t1 : t2;

  if (t < 0.0) {
    return -1.0;
  }

  auto position = rayTransformed(t);

  if (position.y < 0 || position.y > height_) {
    position = rayTransformed(t2);

    if (position.y < 0 || position.y > height_) {
      return -1.0;
    }
  }

  const auto phi = std::atan2(position.z, position.x);
  const auto u = 0.5 * phi * ONE_OVER_PI + 0.5;
  const auto v = position.y / height_;

  Vector3t dpdu(-TAU * position.z, 0.0, TAU * position.x);
  Vector3t dpdv =
      height_ * Vector3t(position.x / (2.0 * position.y), 1.0, position.z / (2.0 * position.y));

  const auto normal = dpdu.cross(dpdv).normalized();
  const auto normalHomogenous = Vector4t(normal, 0.0);

  surfaceInfo.normal =
      ((Vector3t)(transformation_.getToObjectMatrix().transpose() * normalHomogenous)).normalized();
  surfaceInfo.uv = Vector2t(u, v);

  if (surfaceInfo.normal.dot(ray.getDirection()) > 0.0) {
    surfaceInfo.normal = -surfaceInfo.normal;
  }

  return t;
}

Vector3t Paraboloid::sample(RNG&, SurfaceInfo&, Float&) const {
  throw std::runtime_error("Paraboloid sampling is not implemented!");
  return {};
}

#endif