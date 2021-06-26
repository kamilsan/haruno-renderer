#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <memory>

class Color;
class BRDF;

class Material
{
public:
  Material(std::unique_ptr<BRDF> brdf): brdf_(std::move(brdf)) {}

  const BRDF& getBRDF() const { return *brdf_; }

  virtual Color getAlbedo(float u, float v) const = 0;
private:
  std::unique_ptr<BRDF> brdf_;
};

#endif