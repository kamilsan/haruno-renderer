#ifndef TRANSFORMATION_HPP
#define TRANSFORMATION_HPP

#include "Matrix4.hpp"
#include "Ray.hpp"
#include "Types.hpp"

class Transformation {
 public:
  Transformation() : translation_(), scale_(1.0), rotation_(), objectToWorld_(), worldToObject_() {}

  Vector3t toWorldCoordinates(const Vector4t& v) const {
    const auto resultHomogeneous = objectToWorld_ * v;
    return (Vector3t)resultHomogeneous;
  }

  Vector3t toObjectCoordinates(const Vector4t& v) const {
    const auto resultHomogeneous = worldToObject_ * v;
    return (Vector3t)resultHomogeneous;
  }

  Ray toWorldCoordinates(const Ray& ray) const {
    const auto origin = toWorldCoordinates(Vector4t(ray.getOrigin(), static_cast<Float>(1.0)));
    const auto direction =
        toWorldCoordinates(Vector4t(ray.getDirection(), static_cast<Float>(0.0)));

    return Ray(origin, direction);
  }

  Ray toObjectCoordinates(const Ray& ray) const {
    const auto origin = toObjectCoordinates(Vector4(ray.getOrigin(), static_cast<Float>(1.0)));
    const auto direction =
        toObjectCoordinates(Vector4(ray.getDirection(), static_cast<Float>(0.0)));

    return Ray(origin, direction);
  }

  const Matrix4t& getToWorldMatrix() const { return objectToWorld_; }
  const Matrix4t& getToObjectMatrix() const { return worldToObject_; }

  void setTranslation(const Vector3t& translation) {
    translation_ = translation;
    updateMatrices();
  }

  void setScale(const Vector3t& scale) {
    scale_ = scale;
    updateMatrices();
  }

  void setRotation(const Vector3t& rotation) {
    rotation_ = rotation;
    updateMatrices();
  }

 private:
  void updateMatrices();

  Vector3t translation_;
  Vector3t scale_;
  Vector3t rotation_;

  Matrix4t objectToWorld_;
  Matrix4t worldToObject_;
};

#endif  // TRANSFORMATION_HPP