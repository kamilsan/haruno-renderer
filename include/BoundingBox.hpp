#ifndef BOUNDING_BOX_HPP
#define BOUNDING_BOX_HPP

#include <vector>

#include "Vector.hpp"

class Ray;

class BoundingBox {
 public:
  BoundingBox(const Vector& point) : minCorner_(point), maxCorner_(point) {}

  BoundingBox(const Vector& minCorner, const Vector& maxCorner)
      : minCorner_(minCorner), maxCorner_(maxCorner) {}

  BoundingBox(const std::vector<Vector>& points);

  void expand(const Vector& point);
  bool intersects(const Ray& ray) const;

  const Vector& getMinCorner() const { return minCorner_; }

  const Vector& getMaxCorner() const { return maxCorner_; }

 private:
  Vector minCorner_;
  Vector maxCorner_;
};

#endif  // BOUNDING_BOX_HPP