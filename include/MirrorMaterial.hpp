#ifndef MIRROR_MATERIAL_HPP
#define MIRROR_MATEIRAL_HPP

#include "Material.hpp"
#include "SpecularBRDF.hpp"

class MirrorMaterial : public Material
{
public:
  MirrorMaterial(const Color& albedo): 
    Material(std::make_unique<SpecularBRDF>()), albedo_(albedo) {}

  Color getAlbedo() const override { return albedo_; }
private:
  Color albedo_;
};

#endif