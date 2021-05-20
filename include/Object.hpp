#ifndef OBJECT_HPP
#define OBJECT_HPP

class Ray;
class Material;

class Object
{
public:
  Object(std::shared_ptr<Material> material): material_(material) {}

  virtual float intersects(const Ray& ray) const = 0;

  const Material& getMaterial() const { return *material_; }
private:
  std::shared_ptr<Material> material_;
};

#endif