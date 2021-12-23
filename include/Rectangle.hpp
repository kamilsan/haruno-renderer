#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <memory>

#include "Material.hpp"
#include "Object.hpp"
#include "RNG.hpp"
#include "Ray.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"

class Rectangle : public Object {
 public:
  Rectangle(const Vector3f& point, const Vector3f& normal, const Vector3f& tangent,
            const Vector3f& bitangent, float sizeTangent, float sizeBitangent,
            std::shared_ptr<Material> material)
      : Object(material), point_(point), sizeTangent_(sizeTangent), sizeBitangent_(sizeBitangent) {
    // Gram-Schidt process
    normal_ = normal.normalized();
    tangent_ = (tangent - tangent.dot(normal_) * normal_).normalized();
    bitangent_ = (bitangent - bitangent.dot(normal_) * normal_ - bitangent.dot(tangent_) * tangent_)
                     .normalized();

    pdf_ = 1.0f / (sizeTangent * sizeBitangent);
  }

  const Vector3f& getPoint() const { return point_; }
  const Vector3f& getTangent() const { return tangent_; }
  const Vector3f& getBitangent() const { return bitangent_; }

  inline float intersects(const Ray& ray, SurfaceInfo& surfaceInfo) const override;
  inline Vector3f sample(RNG& rng, SurfaceInfo& surfaceInfo, float& pdf) const override;

 private:
  Vector3f point_;
  Vector3f normal_;
  Vector3f tangent_;
  Vector3f bitangent_;
  float sizeTangent_;
  float sizeBitangent_;
  float pdf_;
};

float Rectangle::intersects(const Ray& ray, SurfaceInfo& surfaceInfo) const {
  const float don = ray.getDirection().dot(normal_);
  if (don > -EPSILON && don < EPSILON) {
    return -1;
  }

  const float t = -(ray.getOrigin() - point_).dot(normal_) / don;
  const Vector3f toPosition = ray(t) - point_;

  const float distTangent = toPosition.dot(tangent_);
  if (distTangent < 0.0f || distTangent > sizeTangent_) {
    return -1;
  }

  const float distBitangent = toPosition.dot(bitangent_);
  if (distBitangent < 0.0f || distBitangent > sizeBitangent_) {
    return -1;
  }

  const float u = distTangent / sizeTangent_;
  const float v = distBitangent / sizeBitangent_;

  surfaceInfo.normal = normal_;
  surfaceInfo.uv = Vector2f(u, v);

  return t;
}

Vector3f Rectangle::sample(RNG& rng, SurfaceInfo& surfaceInfo, float& pdf) const {
  const float u = rng.get();
  const float v = rng.get();

  const float s = u * sizeTangent_;
  const float t = v * sizeBitangent_;

  surfaceInfo.normal = normal_;
  surfaceInfo.uv = Vector2f(u, v);

  pdf = pdf_;

  return point_ + tangent_ * s + bitangent_ * t;
}

#endif
