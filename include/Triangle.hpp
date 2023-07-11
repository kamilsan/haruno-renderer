#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "Material.hpp"
#include "Math.hpp"
#include "Object.hpp"
#include "Ray.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"

struct TrianglesData {
  TrianglesData(const std::vector<Vector3t>& vertices, const std::vector<Vector3t>& normals,
                const std::vector<Vector2t>& uvs, const std::vector<unsigned int>& indices)
      : vertices(vertices), normals(normals), uvs(uvs), indices(indices) {}

  std::vector<Vector3t> vertices;
  std::vector<Vector3t> normals;
  std::vector<Vector2t> uvs;
  std::vector<unsigned int> indices;
};

class Triangle : public Object {
 public:
  Triangle(const TrianglesData& trianglesData, unsigned int index,
           std::shared_ptr<Material> material)
      : Object(material), trianglesData_(trianglesData), index_(index) {
    a_ = trianglesData_.vertices[trianglesData_.indices[index_]];
    e1_ = trianglesData_.vertices[trianglesData_.indices[index_ + 1]] - a_;
    e2_ = trianglesData_.vertices[trianglesData_.indices[index_ + 2]] - a_;
    pdf_ = 2.0 / e1_.cross(e2_).length();
  }

  inline Float intersects(const Ray& ray, SurfaceInfo& surfaceInfo) const override;

  inline Vector3t sample(RNG& rng, SurfaceInfo& surfaceInfo, Float& pdf) const override;

 private:
  const TrianglesData& trianglesData_;
  unsigned int index_;
  Float pdf_;
  Vector3t a_;
  Vector3t e1_;
  Vector3t e2_;
};

// Möller, Trumbore - "Fast Minimum Storage Ray-Triangle Intersection"
Float Triangle::intersects(const Ray& ray, SurfaceInfo& surfaceInfo) const {
  constexpr Float EPS = 0.00000001;
  const auto pvec = ray.getDirection().cross(e2_);
  const auto det = e1_.dot(pvec);

  if (det < EPS) {
    return -1;
  }

  const auto tvec = ray.getOrigin() - a_;
  auto u = tvec.dot(pvec);

  if (u < 0.0 || u > det) {
    return -1;
  }

  const auto qvec = tvec.cross(e1_);
  auto v = ray.getDirection().dot(qvec);

  if (v < 0.0 || u + v > det) {
    return -1;
  }

  auto t = e2_.dot(qvec);
  const auto invDet = 1.0 / det;

  t *= invDet;
  u *= invDet;
  v *= invDet;

  const auto normal1 = trianglesData_.normals[trianglesData_.indices[index_]];
  const auto normal2 = trianglesData_.normals[trianglesData_.indices[index_ + 1]];
  const auto normal3 = trianglesData_.normals[trianglesData_.indices[index_ + 2]];

  const auto uv1 = trianglesData_.uvs[trianglesData_.indices[index_]];
  const auto uv2 = trianglesData_.uvs[trianglesData_.indices[index_ + 1]];
  const auto uv3 = trianglesData_.uvs[trianglesData_.indices[index_ + 2]];

  const auto w = 1.0 - u - v;
  surfaceInfo.normal = (w * normal1 + u * normal2 + v * normal3).normalized();
  surfaceInfo.uv = w * uv1 + u * uv2 + v * uv3;

  return t;
}

Vector3t Triangle::sample(RNG& rng, SurfaceInfo& surfaceInfo, Float& pdf) const {
  const auto s = std::sqrt(rng.get());
  const auto u = 1.0 - s;
  const auto v = rng.get() * s;

  const auto normal1 = trianglesData_.normals[trianglesData_.indices[index_]];
  const auto normal2 = trianglesData_.normals[trianglesData_.indices[index_ + 1]];
  const auto normal3 = trianglesData_.normals[trianglesData_.indices[index_ + 2]];

  const auto uv1 = trianglesData_.uvs[trianglesData_.indices[index_]];
  const auto uv2 = trianglesData_.uvs[trianglesData_.indices[index_ + 1]];
  const auto uv3 = trianglesData_.uvs[trianglesData_.indices[index_ + 2]];

  const auto w = 1.0 - u - v;
  surfaceInfo.normal = (w * normal1 + u * normal2 + v * normal3).normalized();
  surfaceInfo.uv = w * uv1 + u * uv2 + v * uv3;

  pdf = pdf_;

  return a_ + u * e1_ + v * e2_;
}

#endif