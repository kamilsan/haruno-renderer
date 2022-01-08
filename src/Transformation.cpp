#include "Transformation.hpp"

void Transformation::updateMatrices() {
  const auto rotationMatrix = Matrix4f::initRotation(rotation_);

  objectToWorld_ =
      Matrix4f::initTranslation(translation_) * Matrix4f::initScaling(scale_) * rotationMatrix;

  worldToObject_ =
      rotationMatrix.transpose() *
      Matrix4f::initScaling(Vector3f(1.0f / scale_.x, 1.0f / scale_.y, 1.0f / scale_.z)) *
      Matrix4f::initTranslation(-translation_);
}