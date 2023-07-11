#include "Transformation.hpp"

void Transformation::updateMatrices() {
  const auto rotationMatrix = Matrix4t::initRotation(rotation_);

  objectToWorld_ =
      Matrix4t::initTranslation(translation_) * Matrix4t::initScaling(scale_) * rotationMatrix;

  worldToObject_ = rotationMatrix.transpose() *
                   Matrix4t::initScaling(Vector3t(1.0 / scale_.x, 1.0 / scale_.y, 1.0 / scale_.z)) *
                   Matrix4t::initTranslation(-translation_);
}