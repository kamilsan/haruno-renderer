#ifndef CONE_HPP
#define CONE_HPP

#include "Material.hpp"
#include "Math.hpp"
#include "Object.hpp"
#include "Ray.hpp"
#include "Transformation.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"

class Cone : public Object {
 public:
  Cone(const Transformation& transformation, float radius, float height,
       std::shared_ptr<Material> material)
      : Object(material), transformation_(transformation), radius_(radius), height_(height) {}

  float getRadius() const { return radius_; }
  float getHeight() const { return height_; }

  inline float intersects(const Ray& ray, SurfaceInfo& surfaceInfo) const override;
  inline Vector3f sample(RNG& rng, SurfaceInfo& surfaceInfo, float& pdf) const override;

 private:
  Transformation transformation_;
  float radius_;
  float height_;
};

float Cone::intersects(const Ray& ray, SurfaceInfo& surfaceInfo) const {
  const auto rayTransformed = transformation_.toObjectCoordinates(ray);

  const auto& origin = rayTransformed.getOrigin();
  const auto& direction = rayTransformed.getDirection();

  auto k = height_ / radius_;
  k = k * k;

  const float a =
      k * (direction.x * direction.x + direction.z * direction.z) - direction.y * direction.y;
  const float b = 2.0f * k * (origin.x * direction.x + origin.z * direction.z) -
                  2.0f * direction.y * (origin.y - height_);
  const float c =
      k * (origin.x * origin.x + origin.z * origin.z) - (origin.y - height_) * (origin.y - height_);

  float t1, t2;
  if (!solveQuadratic(a, b, c, t1, t2)) {
    return -1.0f;
  }

  const float t = t1 > 0.0f ? t1 : t2;

  if (t < 0.0f) {
    return -1.0f;
  }

  auto position = rayTransformed(t);

  if (position.y < 0 || position.y > height_) {
    position = rayTransformed(t2);

    if (position.y < 0 || position.y > height_) {
      return -1.0f;
    }
  }

  const auto phi = std::atan2(position.z, position.x);
  const auto u = 0.5f * phi * ONE_OVER_PI + 0.5f;
  const auto v = position.y / height_;

  Vector3f dpdu(-TAU * position.z, 0.0f, TAU * position.x);
  Vector3f dpdv(-position.x / (1.0f - v), height_, -position.z / (1.0f - v));

  const auto normal = dpdu.cross(dpdv).normalized();
  const auto normalHomogenous = Vector4f(normal, 0.0f);

  surfaceInfo.normal =
      ((Vector3f)(transformation_.getToObjectMatrix().transpose() * normalHomogenous)).normalized();
  surfaceInfo.uv = Vector2f(u, v);

  if (surfaceInfo.normal.dot(ray.getDirection()) > 0.0f) {
    surfaceInfo.normal = -surfaceInfo.normal;
  }

  return t;
}

Vector3f Cone::sample(RNG&, SurfaceInfo&, float&) const {
  throw std::runtime_error("Cone sampling is not implemented!");
  return {};
}

#endif