#include "BoundingBox.hpp"

#include "Ray.hpp"

BoundingBox::BoundingBox(const std::vector<Vector>& points) {
  if (points.size() > 0) {
    minCorner_ = points[0];
    maxCorner_ = points[0];

    for (const auto& point : points) {
      expand(point);
    }
  }
}

void BoundingBox::expand(const Vector& point) {
  if (point.x < minCorner_.x) {
    minCorner_.x = point.x;
  } else if (point.x > maxCorner_.x) {
    maxCorner_.x = point.x;
  }

  if (point.y < minCorner_.y) {
    minCorner_.y = point.y;
  } else if (point.y > maxCorner_.y) {
    maxCorner_.y = point.y;
  }

  if (point.z < minCorner_.z) {
    minCorner_.z = point.z;
  } else if (point.z > maxCorner_.z) {
    maxCorner_.z = point.z;
  }
}

bool BoundingBox::intersects(const Ray& ray) const {
  // TODO
  return true;
}