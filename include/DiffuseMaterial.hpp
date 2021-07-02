#ifndef SOLID_MATERIAL_HPP
#define SOLID_MATEIRAL_HPP

#include <memory>

#include "BaseTexture.hpp"
#include "LambertBRDF.hpp"
#include "Material.hpp"

class DiffuseMaterial : public Material {
 public:
  DiffuseMaterial(std::shared_ptr<BaseTexture> albedo, float diffuseFactor)
      : Material(std::make_unique<LambertBRDF>(diffuseFactor)), albedo_(albedo) {}

  Color getAlbedo(float u, float v) const override { return albedo_->get(u, v); }

 private:
  std::shared_ptr<BaseTexture> albedo_;
};

#endif