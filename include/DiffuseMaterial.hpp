#ifndef SOLID_MATERIAL_HPP
#define SOLID_MATERIAL_HPP

#include <memory>

#include "BaseTexture.hpp"
#include "LambertBRDF.hpp"
#include "Material.hpp"

class DiffuseMaterial : public Material {
 public:
  DiffuseMaterial(std::shared_ptr<BaseTexture> albedo, Float diffuseFactor)
      : Material(std::make_unique<LambertBRDF>(diffuseFactor)), albedo_(albedo) {}

  Color getAlbedo(const Vector2t& uv) const override { return albedo_->get(uv); }

 private:
  std::shared_ptr<BaseTexture> albedo_;
};

#endif  // SOLID_MATERIAL_HPP