#ifndef TEXTURE_ENVIRONMENT_HPP
#define TEXTURE_ENVIRONMENT_HPP

#include <memory>

#include "BaseTexture.hpp"
#include "Environment.hpp"
#include "Vector3.hpp"

class TextureEnvironment : public Environment {
 public:
  TextureEnvironment(std::shared_ptr<BaseTexture> texture) : texture_(texture) {}

  Color getColor(const Vector3t& direction) const override;

 private:
  std::shared_ptr<BaseTexture> texture_;
};

#endif