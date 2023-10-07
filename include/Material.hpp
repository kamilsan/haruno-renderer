#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <memory>

#include "BRDF.hpp"
#include "Vector2.hpp"

class Color;

class Material {
 public:
  Material(std::unique_ptr<BRDF> brdf) : brdf_(std::move(brdf)) {}
  virtual ~Material() = default;

  const BRDF& getBRDF() const { return *brdf_; }

  virtual Color getAlbedo(const Vector2t& uv) const = 0;

 private:
  std::unique_ptr<BRDF> brdf_;
};

#endif