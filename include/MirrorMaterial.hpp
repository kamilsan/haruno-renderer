#ifndef MIRROR_MATERIAL_HPP
#define MIRROR_MATEIRAL_HPP

#include "Material.hpp"
#include "BaseTexture.hpp"
#include "SpecularBRDF.hpp"

#include <memory>

class MirrorMaterial : public Material
{
public:
  MirrorMaterial(std::shared_ptr<BaseTexture> albedo): 
    Material(std::make_unique<SpecularBRDF>()), albedo_(albedo) {}

  Color getAlbedo(float u, float v) const override { return albedo_->get(u, v); }
private:
  std::shared_ptr<BaseTexture> albedo_;
};

#endif