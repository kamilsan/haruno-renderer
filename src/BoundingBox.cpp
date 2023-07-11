#include "BoundingBox.hpp"

#include "Ray.hpp"
#include "Sphere.hpp"

BoundingBox::BoundingBox(const std::vector<Vector3t>& points) {
  if (points.size() > 0) {
    minCorner_ = points[0];
    maxCorner_ = points[0];

    for (const auto& point : points) {
      expand(point);
    }
  }
}

void BoundingBox::expand(const Vector3t& point) {
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
  Float intersectionIntervalMin = 0.0;
  Float intersectionIntervalMax = std::numeric_limits<Float>::max();

  for (size_t i = 0; i < 3; ++i) {
    const Float invDirection = 1.0 / ray.getDirection()[i];
    Float tMin = (minCorner_[i] - ray.getOrigin()[i]) * invDirection;
    Float tMax = (maxCorner_[i] - ray.getOrigin()[i]) * invDirection;
    if (tMin > tMax) {
      std::swap(tMin, tMax);
    }

    if (tMin > intersectionIntervalMin) {
      intersectionIntervalMin = tMin;
    }
    if (tMax < intersectionIntervalMax) {
      intersectionIntervalMax = tMax;
    }

    if (intersectionIntervalMin > intersectionIntervalMax) {
      return false;
    }
  }

  return true;
}