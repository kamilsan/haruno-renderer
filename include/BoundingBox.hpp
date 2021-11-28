#ifndef BOUNDING_BOX_HPP
#define BOUNDING_BOX_HPP

#include <vector>

#include "Vector3.hpp"

class Ray;

class BoundingBox {
 public:
  BoundingBox(const Vector3f& point) : minCorner_(point), maxCorner_(point) {}

  BoundingBox(const Vector3f& minCorner, const Vector3f& maxCorner)
      : minCorner_(minCorner), maxCorner_(maxCorner) {}

  BoundingBox(const std::vector<Vector3f>& points);

  void expand(const Vector3f& point);
  bool intersects(const Ray& ray) const;

  const Vector3f& getMinCorner() const { return minCorner_; }
  const Vector3f& getMaxCorner() const { return maxCorner_; }

 private:
  Vector3f minCorner_;
  Vector3f maxCorner_;
};

#endif  // BOUNDING_BOX_HPP