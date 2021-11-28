#include "Transformation.hpp"

void Transformation::updateMatrices() {
  objectToWorld_ = Matrix4f::initTranslation(translation_) * Matrix4f::initScaling(scale_) *
                   Matrix4f::initRotation(rotation_);

  worldToObject_ =
      Matrix4f::initRotation(-rotation_) *
      Matrix4f::initScaling(Vector3f(1.0f / scale_.x, 1.0f / scale_.y, 1.0f / scale_.z)) *
      Matrix4f::initTranslation(-translation_);
}