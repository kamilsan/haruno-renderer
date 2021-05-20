#ifndef MATERIAL_HPP
#define MATERIAL_HPP

class Color;

class Material
{
public:
  virtual Color getAlbedo() const = 0;
};

#endif