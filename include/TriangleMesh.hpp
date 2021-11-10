#ifndef TRIANGLE_MESH_HPP
#define TRIANGLE_MESH_HPP

#include <memory>
#include <vector>

#include "BoundingBox.hpp"
#include "Object.hpp"
#include "Triangle.hpp"

class TriangleMesh : public Object {
 public:
  inline TriangleMesh(const std::vector<Vector>& vertices, const std::vector<unsigned int>& indices,
                      std::shared_ptr<Material> material);

  inline float intersects(const Ray& ray, SurfaceInfo& surfaceInfo) const override;

 private:
  std::vector<Triangle> triangles_;
  BoundingBox boundingBox_;
};

inline TriangleMesh::TriangleMesh(const std::vector<Vector>& vertices,
                                  const std::vector<unsigned int>& indices,
                                  std::shared_ptr<Material> material)
    : Object(material), boundingBox_(vertices) {
  for (size_t i = 0; i < indices.size(); i += 3) {
    const auto& v1 = vertices[indices[i]];
    const auto& v2 = vertices[indices[i + 1]];
    const auto& v3 = vertices[indices[i + 2]];

    triangles_.emplace_back(Triangle(v1, v2, v3, material));
  }

  std::cout << "Min corner: " << boundingBox_.getMinCorner() << "\n";
  std::cout << "Max corner: " << boundingBox_.getMaxCorner() << "\n";
}

inline float TriangleMesh::intersects(const Ray& ray, SurfaceInfo& surfaceInfo) const {
  float minT = -1;
  SurfaceInfo tempSurfaceInfo;

  if (boundingBox_.intersects(ray)) {
    for (const auto& triangle : triangles_) {
      const auto t = triangle.intersects(ray, tempSurfaceInfo);
      if (t > 0 && (t < minT || minT < 0.0f)) {
        minT = t;
        surfaceInfo = tempSurfaceInfo;
      }
    }
  }

  return minT;
}

#endif  // TRIANGLE_MESH_HPP