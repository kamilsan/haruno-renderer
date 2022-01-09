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
  Cylinder(const Transformation& transformation, float radius, float height,
           std::shared_ptr<Material> material)
      : Object(material), transformation_(transformation), radius_(radius), height_(height) {
    pdf_ = 1.0f / (2.0f * PI * radius * height);
  }

  float getRadius() const { return radius_; }
  float getHeight() const { return height_; }

  inline float intersects(const Ray& ray, SurfaceInfo& surfaceInfo) const override;
  inline Vector3f sample(RNG& rng, SurfaceInfo& surfaceInfo, float& pdf) const override;

 private:
  Transformation transformation_;
  float radius_;
  float height_;
  float pdf_;
};

float Cylinder::intersects(const Ray& ray, SurfaceInfo& surfaceInfo) const {
  const auto rayTransformed = transformation_.toObjectCoordinates(ray);

  const auto& origin = rayTransformed.getOrigin();
  const auto& direction = rayTransformed.getDirection();

  const float a = direction.x * direction.x + direction.z * direction.z;
  const float b = 2.0f * (origin.x * direction.x + origin.z * direction.z);
  const float c = origin.x * origin.x + origin.z * origin.z - radius_ * radius_;

  float t1, t2;
  if (!solveQuadratic(a, b, c, t1, t2)) {
    return -1.0f;
  }

  const float t = t1 > 0.0f ? t1 : t2;

  if (t < 0.0f) {
    return -1.0f;
  }

  auto position = rayTransformed(t);

  if (2.0f * std::abs(position.y) > height_) {
    position = rayTransformed(t2);

    if (2.0f * std::abs(position.y) > height_) {
      return -1.0f;
    }
  }

  const auto normal = Vector3f(position.x, 0, position.z) / radius_;
  const auto normalHomogenous = Vector4f(normal, 0.0f);

  const auto phi = std::atan2(position.z, position.x);
  const auto u = 0.5f * phi * ONE_OVER_PI + 0.5f;
  const auto v = position.y / height_ - 0.5f;

  surfaceInfo.normal =
      ((Vector3f)(transformation_.getToObjectMatrix().transpose() * normalHomogenous)).normalized();
  surfaceInfo.uv = Vector2f(u, v);

  if (surfaceInfo.normal.dot(ray.getDirection()) > 0.0f) {
    surfaceInfo.normal = -surfaceInfo.normal;
  }

  return t;
}

Vector3f Cylinder::sample(RNG& rng, SurfaceInfo& surfaceInfo, float& pdf) const {
  const float u = rng.get();
  const float v = rng.get();

  const float y = (v - 0.5f) * height_;
  const float phi = TAU * u;

  const float sinPhi = std::sin(phi);
  const float cosPhi = std::cos(phi);

  const auto normal = Vector3f(cosPhi, 0, sinPhi);
  const auto normalHomogenous = Vector4f(normal, 0.0f);

  const auto position = radius_ * normal + Vector3f(0.0f, y, 0.0f);

  surfaceInfo.normal =
      ((Vector3f)(transformation_.getToObjectMatrix().transpose() * normalHomogenous)).normalized();
  surfaceInfo.uv = Vector2f(u, v);

  pdf = pdf_;

  return transformation_.toWorldCoordinates(Vector4f(position, 1.0f));
}

#endif