#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "Object.hpp"
#include "Vector.hpp"
#include "Ray.hpp"
#include "Material.hpp"

#include <memory>

class Rectangle : public Object
{
public:
  Rectangle(const Vector& point, const Vector& normal, const Vector& tangent, const Vector& bitangent, 
    float sizeTangent, float sizeBitangent, std::shared_ptr<Material> material): 
    Object(material), point_(point), sizeTangent_(sizeTangent), sizeBitangent_(sizeBitangent)
  {
    // Gram-Schidt process
    normal_ = normal.normalized();
    tangent_ = (tangent - tangent.dot(normal_) * normal_).normalized();
    bitangent_ = (bitangent - bitangent.dot(normal_) * normal_ - bitangent.dot(tangent_) * tangent_).normalized();
  }

  const Vector& getPoint() const { return point_; }
  const Vector& getTangent() const { return tangent_; }
  const Vector& getBitangent() const { return bitangent_; }

  inline float intersects(const Ray& ray) const override;
  inline SurfaceInfo getSurfaceInfo(const Vector& position) const override;

private:
  Vector point_;
  Vector normal_;
  Vector tangent_;
  Vector bitangent_;
  float sizeTangent_;
  float sizeBitangent_;
};

float Rectangle::intersects(const Ray& ray) const
{
  const float don = ray.getDirection().dot(normal_);
  if(don > -0.00001f && don < 0.00001f) 
    return -1;

  const float t = -(ray.getOrigin() - point_).dot(normal_) / don;
  const Vector toPosition = ray(t) - point_;

  const float distTangent = toPosition.dot(tangent_);
  if(distTangent < 0.0f || distTangent > sizeTangent_)
    return -1;

  const float distBitangent = toPosition.dot(bitangent_);
  if(distBitangent < 0.0f || distBitangent > sizeBitangent_)
    return -1;

  return t;
}

SurfaceInfo Rectangle::getSurfaceInfo(const Vector& position) const
{
  const auto fromPlanePoint = position - point_;

  const float u = fromPlanePoint.dot(tangent_) / sizeTangent_;
  const float v = fromPlanePoint.dot(bitangent_) / sizeBitangent_;
  
  return SurfaceInfo{normal_, u, v};
}

#endif
