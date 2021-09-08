#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "Material.hpp"
#include "Math.hpp"
#include "Object.hpp"
#include "Ray.hpp"
#include "Vector.hpp"

class Triangle : public Object {
 public:
  Triangle(const Vector& a, const Vector& b, const Vector& c, std::shared_ptr<Material> material)
      : Object(material), a_(a), e1_(b - a), e2_(c - a) {
    normal_ = e1_.cross(e2_);
  }

  inline float intersects(const Ray& ray, SurfaceInfo& surfaceInfo) const override;

 private:
  Vector a_;
  Vector e1_;
  Vector e2_;
  Vector normal_;
};

//  Möller, Trumbore - "Fast Minimum Storage Ray-Triangle Intersection"
float Triangle::intersects(const Ray& ray, SurfaceInfo& surfaceInfo) const {
  const auto pvec = ray.getDirection().cross(e2_);
  const auto det = e1_.dot(pvec);

  if (det < EPSILON) {
    return -1;
  }

  const auto tvec = ray.getOrigin() - a_;
  auto u = tvec.dot(pvec);

  if (u < 0.0f || u > det) {
    return -1;
  }

  const auto qvec = tvec.cross(e1_);
  auto v = ray.getDirection().dot(qvec);

  if (v < 0.0f || u + v > det) {
    return -1;
  }

  auto t = e2_.dot(qvec);
  const auto invDet = 1.0f / det;

  t *= invDet;
  u *= invDet;
  v *= invDet;

  surfaceInfo.normal = normal_;
  surfaceInfo.uv = std::make_pair(u, v);

  return t;
}

#endif