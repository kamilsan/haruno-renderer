#ifndef SOLID_MATERIAL_HPP
#define SOLID_MATEIRAL_HPP

#include "Material.hpp"
#include "LambertBRDF.hpp"

class SolidMaterial : public Material
{
public:
  SolidMaterial(const Color& albedo): Material(std::make_unique<LambertBRDF>()), albedo_(albedo) {}

  Color getAlbedo() const override { return albedo_; }

private:
  Color albedo_;
};

#endif