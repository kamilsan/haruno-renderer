#ifndef BOUNDING_BOX_HPP
#define BOUNDING_BOX_HPP

#include <vector>

#include "Types.hpp"

class Ray;

class BoundingBox {
 public:
  BoundingBox(const Vector3t& point) : minCorner_(point), maxCorner_(point) {}

  BoundingBox(const Vector3t& minCorner, const Vector3t& maxCorner)
      : minCorner_(minCorner), maxCorner_(maxCorner) {}

  BoundingBox(const std::vector<Vector3t>& points);

  void expand(const Vector3t& point);
  bool intersects(const Ray& ray) const;

  const Vector3t& getMinCorner() const { return minCorner_; }
  const Vector3t& getMaxCorner() const { return maxCorner_; }

 private:
  Vector3t minCorner_;
  Vector3t maxCorner_;
};

#endif  // BOUNDING_BOX_HPP