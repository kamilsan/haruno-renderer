#ifndef MIRROR_MATERIAL_HPP
#define MIRROR_MATEIRAL_HPP

#include <memory>

#include "BaseTexture.hpp"
#include "Material.hpp"
#include "SpecularBRDF.hpp"

class MirrorMaterial : public Material {
 public:
  MirrorMaterial(std::shared_ptr<BaseTexture> albedo)
      : Material(std::make_unique<SpecularBRDF>()), albedo_(albedo) {}

  Color getAlbedo(const Vector2f& uv) const override { return albedo_->get(uv); }

 private:
  std::shared_ptr<BaseTexture> albedo_;
};

#endif