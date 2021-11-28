#include "BoundingBox.hpp"

#include "Ray.hpp"
#include "Sphere.hpp"

BoundingBox::BoundingBox(const std::vector<Vector3f>& points) {
  if (points.size() > 0) {
    minCorner_ = points[0];
    maxCorner_ = points[0];

    for (const auto& point : points) {
      expand(point);
    }
  }
}

void BoundingBox::expand(const Vector3f& point) {
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
  float intersectionIntervalMin = 0.0f;
  float intersectionIntervalMax = std::numeric_limits<float>::max();

  for (size_t i = 0; i < 3; ++i) {
    const float invDirection = 1.0f / ray.getDirection()[i];
    float tMin = (minCorner_[i] - ray.getOrigin()[i]) * invDirection;
    float tMax = (maxCorner_[i] - ray.getOrigin()[i]) * invDirection;
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