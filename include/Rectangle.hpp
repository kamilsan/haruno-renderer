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
  Rectangle(const Vector3t& point, const Vector3t& normal, const Vector3t& tangent,
            const Vector3t& bitangent, Float sizeTangent, Float sizeBitangent,
            std::shared_ptr<Material> material)
      : Object(material), point_(point), sizeTangent_(sizeTangent), sizeBitangent_(sizeBitangent) {
    // Gram-Schmidt process
    normal_ = normal.normalized();
    tangent_ = (tangent - tangent.dot(normal_) * normal_).normalized();
    bitangent_ = (bitangent - bitangent.dot(normal_) * normal_ - bitangent.dot(tangent_) * tangent_)
                     .normalized();

    pdf_ = 1.0 / (sizeTangent * sizeBitangent);
  }

  const Vector3t& getPoint() const { return point_; }
  const Vector3t& getTangent() const { return tangent_; }
  const Vector3t& getBitangent() const { return bitangent_; }

  inline Float intersects(const Ray& ray, SurfaceInfo& surfaceInfo) const override;
  inline Vector3t sample(RNG& rng, SurfaceInfo& surfaceInfo, Float& pdf) const override;

 private:
  Vector3t point_;
  Vector3t normal_;
  Vector3t tangent_;
  Vector3t bitangent_;
  Float sizeTangent_;
  Float sizeBitangent_;
  Float pdf_;
};

Float Rectangle::intersects(const Ray& ray, SurfaceInfo& surfaceInfo) const {
  const Float don = ray.getDirection().dot(normal_);
  if (don > -EPSILON && don < EPSILON) {
    return -1;
  }

  const Float t = -(ray.getOrigin() - point_).dot(normal_) / don;
  const Vector3t toPosition = ray(t) - point_;

  const Float distTangent = toPosition.dot(tangent_);
  if (distTangent < 0.0 || distTangent > sizeTangent_) {
    return -1;
  }

  const Float distBitangent = toPosition.dot(bitangent_);
  if (distBitangent < 0.0 || distBitangent > sizeBitangent_) {
    return -1;
  }

  const Float u = distTangent / sizeTangent_;
  const Float v = distBitangent / sizeBitangent_;

  surfaceInfo.normal = normal_;
  surfaceInfo.uv = Vector2t(u, v);

  return t;
}

Vector3t Rectangle::sample(RNG& rng, SurfaceInfo& surfaceInfo, Float& pdf) const {
  const Float u = rng.get();
  const Float v = rng.get();

  const Float s = u * sizeTangent_;
  const Float t = v * sizeBitangent_;

  surfaceInfo.normal = normal_;
  surfaceInfo.uv = Vector2t(u, v);

  pdf = pdf_;

  return point_ + tangent_ * s + bitangent_ * t;
}

#endif
