#ifndef TRIANGLE_MESH_HPP
#define TRIANGLE_MESH_HPP

#include <memory>
#include <vector>

#include "BoundingBox.hpp"
#include "Object.hpp"
#include "Transformation.hpp"
#include "Triangle.hpp"
#include "Vector2.hpp"

class TriangleMesh : public Object {
 public:
  inline TriangleMesh(const std::vector<Vector3t>& vertices, const std::vector<Vector3t>& normals,
                      const std::vector<Vector2t>& uvs, const std::vector<unsigned int>& indices,
                      const Transformation& transformation, std::shared_ptr<Material> material);

  inline Float intersects(const Ray& ray, SurfaceInfo& surfaceInfo) const override;
  inline Vector3t sample(RNG& rng, SurfaceInfo& surfaceInfo, Float& pdf) const override;

 private:
  TrianglesData trianglesData_;
  std::vector<Triangle> triangles_;
  BoundingBox boundingBox_;
  Transformation transformation_;
};

inline TriangleMesh::TriangleMesh(const std::vector<Vector3t>& vertices,
                                  const std::vector<Vector3t>& normals,
                                  const std::vector<Vector2t>& uvs,
                                  const std::vector<unsigned int>& indices,
                                  const Transformation& transformation,
                                  std::shared_ptr<Material> material)
    : Object(material),
      trianglesData_(vertices, normals, uvs, indices),
      boundingBox_(vertices),
      transformation_(transformation) {
  for (size_t i = 0; i < indices.size(); i += 3) {
    const auto triangle = Triangle(trianglesData_, i, material);
    triangles_.emplace_back(triangle);
  }
}

inline Float TriangleMesh::intersects(const Ray& ray, SurfaceInfo& surfaceInfo) const {
  Float minT = -1;
  SurfaceInfo tempSurfaceInfo;

  // After this transformation ray direction may not be normalized
  // and we do not want to normalize it, so as to get reasonable t values
  const Ray rayTransformed = transformation_.toObjectCoordinates(ray);

  if (boundingBox_.intersects(rayTransformed)) {
    for (const auto& triangle : triangles_) {
      const auto t = triangle.intersects(rayTransformed, tempSurfaceInfo);
      if (t > 0 && (t < minT || minT < 0.0)) {
        minT = t;
        surfaceInfo = tempSurfaceInfo;
      }
    }
  }

  const auto normalHomogenous = Vector4t(surfaceInfo.normal, 0.0);
  surfaceInfo.normal =
      ((Vector3t)(transformation_.getToObjectMatrix().transpose() * normalHomogenous)).normalized();

  return minT;
}

Vector3t TriangleMesh::sample(RNG& rng, SurfaceInfo& surfaceInfo, Float& pdf) const {
  const size_t idx = rng.get() * triangles_.size();
  const auto& triangle = triangles_[idx];

  Float trianglePdf;
  const auto triangleSample = triangle.sample(rng, surfaceInfo, trianglePdf);

  pdf = (1.0 / triangles_.size()) * trianglePdf;

  return transformation_.toWorldCoordinates(Vector4t(triangleSample, 1.0));
}

#endif  // TRIANGLE_MESH_HPP