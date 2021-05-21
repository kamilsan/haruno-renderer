#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Object.hpp"
#include "Vector.hpp"
#include "Ray.hpp"
#include "Material.hpp"

#include <cmath>

class Sphere : public Object
{
public:
  Sphere(const Vector& center, float radius, std::shared_ptr<Material> material): 
    Object(material), center_(center), radius_(radius) {}

  const Vector& getCenter() const { return center_; }
  float getRadius() const { return radius_; }

  inline float intersects(const Ray& ray) const override;
  inline Vector getNormal(const Vector& position) const override;

private:
  Vector center_;
  float radius_;
};

// NOTE: Ray direction is assumed to be normalized
float Sphere::intersects(const Ray& ray) const
{
  // TODO: Use more numerically stable method
  Vector centerToOrigin = ray.getOrigin() - center_;
  const float b = 2.0f * ray.getDirection().dot(centerToOrigin);
  const float c = centerToOrigin.dot(centerToOrigin) - radius_ * radius_;
  float delta = b * b - 4.0f * c;
  if(delta < 0.0f)
    return -1.0f;

  delta = std::sqrt(delta);

  const float t1 = (-b - delta) * 0.5f;
  const float t2 = (-b + delta) * 0.5f;

  return (t1 < t2 ? t1 : t2);
}

Vector Sphere::getNormal(const Vector& position) const
{
  return (position - center_) / radius_;
}

#endif