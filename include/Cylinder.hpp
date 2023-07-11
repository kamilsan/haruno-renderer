#ifndef CYLINDER_HPP
#define CYLINDER_HPP

#include "Material.hpp"
#include "Math.hpp"
#include "Object.hpp"
#include "Ray.hpp"
#include "Transformation.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"

class Cylinder : public Object {
 public:
  Cylinder(const Transformation& transformation, Float radius, Float height,
           std::shared_ptr<Material> material)
      : Object(material), transformation_(transformation), radius_(radius), height_(height) {
    pdf_ = 1.0 / (2.0 * PI * radius * height);
  }

  Float getRadius() const { return radius_; }
  Float getHeight() const { return height_; }

  inline Float intersects(const Ray& ray, SurfaceInfo& surfaceInfo) const override;
  inline Vector3t sample(RNG& rng, SurfaceInfo& surfaceInfo, Float& pdf) const override;

 private:
  Transformation transformation_;
  Float radius_;
  Float height_;
  Float pdf_;
};

Float Cylinder::intersects(const Ray& ray, SurfaceInfo& surfaceInfo) const {
  const auto rayTransformed = transformation_.toObjectCoordinates(ray);

  const auto& origin = rayTransformed.getOrigin();
  const auto& direction = rayTransformed.getDirection();

  const Float a = direction.x * direction.x + direction.z * direction.z;
  const Float b = 2.0 * (origin.x * direction.x + origin.z * direction.z);
  const Float c = origin.x * origin.x + origin.z * origin.z - radius_ * radius_;

  Float t1, t2;
  if (!solveQuadratic(a, b, c, t1, t2)) {
    return -1.0;
  }

  const Float t = t1 > 0.0 ? t1 : t2;

  if (t < 0.0) {
    return -1.0;
  }

  auto position = rayTransformed(t);

  if (2.0 * std::abs(position.y) > height_) {
    position = rayTransformed(t2);

    if (2.0 * std::abs(position.y) > height_) {
      return -1.0;
    }
  }

  const auto normal = Vector3t(position.x, 0, position.z) / radius_;
  const auto normalHomogenous = Vector4t(normal, 0.0);

  const auto phi = std::atan2(position.z, position.x);
  const auto u = 0.5 * phi * ONE_OVER_PI + 0.5;
  const auto v = position.y / height_ - 0.5;

  surfaceInfo.normal =
      ((Vector3t)(transformation_.getToObjectMatrix().transpose() * normalHomogenous)).normalized();
  surfaceInfo.uv = Vector2t(u, v);

  if (surfaceInfo.normal.dot(ray.getDirection()) > 0.0) {
    surfaceInfo.normal = -surfaceInfo.normal;
  }

  return t;
}

Vector3t Cylinder::sample(RNG& rng, SurfaceInfo& surfaceInfo, Float& pdf) const {
  const Float u = rng.get();
  const Float v = rng.get();

  const Float y = (v - 0.5) * height_;
  const Float phi = TAU * u;

  const Float sinPhi = std::sin(phi);
  const Float cosPhi = std::cos(phi);

  const auto normal = Vector3t(cosPhi, 0, sinPhi);
  const auto normalHomogenous = Vector4t(normal, 0.0);

  const auto position = radius_ * normal + Vector3t(0.0, y, 0.0);

  surfaceInfo.normal =
      ((Vector3t)(transformation_.getToObjectMatrix().transpose() * normalHomogenous)).normalized();
  surfaceInfo.uv = Vector2t(u, v);

  pdf = pdf_;

  return transformation_.toWorldCoordinates(Vector4t(position, 1.0));
}

#endif