#ifndef PLANE_HPP
#define PLANE_HPP

#include "Object.hpp"
#include "Vector.hpp"
#include "Ray.hpp"
#include "Material.hpp"

#include <memory>

class Plane : public Object
{
public:
  Plane(const Vector& point, const Vector& normal, std::shared_ptr<Material> material): 
    Object(material), point_(point), normal_(normal) {}

  const Vector& getPoint() const { return point_; }
  const Vector& getNormal() const { return normal_; }

  inline float intersects(const Ray& ray) const override;

private:
  Vector point_;
  Vector normal_;
};

float Plane::intersects(const Ray& ray) const
{
  const float don = ray.getDirection().dot(normal_);
  if(don > -0.00001f && don < 0.00001f) 
    return -1;

  return -(ray.getOrigin() - point_).dot(normal_) / don;
}

#endif
