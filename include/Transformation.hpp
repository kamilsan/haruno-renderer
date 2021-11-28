#ifndef TRANSFORMATION_HPP
#define TRANSFORMATION_HPP

#include "Matrix4.hpp"
#include "Ray.hpp"

class Transformation {
 public:
  Transformation()
      : translation_(), scale_(1.0f), rotation_(), objectToWorld_(), worldToObject_() {}

  Vector3f toWorldCoordinates(const Vector4f& v) const {
    const auto resultHomogeneous = objectToWorld_ * v;
    return (Vector3f)resultHomogeneous;
  }

  Vector3f toObjectCoordinates(const Vector4f& v) const {
    const auto resultHomogeneous = worldToObject_ * v;
    return (Vector3f)resultHomogeneous;
  }

  Ray toWorldCoordinates(const Ray& ray) const {
    const auto origin = toWorldCoordinates(Vector4f(ray.getOrigin(), 1.0f));
    const auto direction = toWorldCoordinates(Vector4f(ray.getDirection(), 0.0f));

    return Ray(origin, direction);
  }

  Ray toObjectCoordinates(const Ray& ray) const {
    const auto origin = toObjectCoordinates(Vector4(ray.getOrigin(), 1.0f));
    const auto direction = toObjectCoordinates(Vector4(ray.getDirection(), 0.0f));

    return Ray(origin, direction);
  }

  const Matrix4f& getToWorldMatrix() const { return objectToWorld_; }
  const Matrix4f& getToObjectMatrix() const { return worldToObject_; }

  void setTranslation(const Vector3f& translation) {
    translation_ = translation;
    updateMatrices();
  }

  void setScale(const Vector3f& scale) {
    scale_ = scale;
    updateMatrices();
  }

  void setRotation(const Vector3f& rotation) {
    rotation_ = rotation;
    updateMatrices();
  }

 private:
  void updateMatrices();

  Vector3f translation_;
  Vector3f scale_;
  Vector3f rotation_;

  Matrix4f objectToWorld_;
  Matrix4f worldToObject_;
};

#endif  // TRANSFORMATION_HPP