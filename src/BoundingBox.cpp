#include "BoundingBox.hpp"

#include "Ray.hpp"
#include "Sphere.hpp"

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
  float intersectionIntervalMin = 0.0f;
  float intersectionIntervalMax = std::numeric_limits<float>::max();

  // x
  const float invDirectionX = 1.0f / ray.getDirection().x;
  float tMinX = (minCorner_.x - ray.getOrigin().x) * invDirectionX;
  float tMaxX = (maxCorner_.x - ray.getOrigin().x) * invDirectionX;
  if (tMinX > tMaxX) {
    std::swap(tMinX, tMaxX);
  }

  if (tMinX > intersectionIntervalMin) {
    intersectionIntervalMin = tMinX;
  }
  if (tMaxX < intersectionIntervalMax) {
    intersectionIntervalMax = tMaxX;
  }
  if (intersectionIntervalMin > intersectionIntervalMax) {
    return false;
  }

  // y
  const float invDirectionY = 1.0f / ray.getDirection().y;
  float tMinY = (minCorner_.y - ray.getOrigin().y) * invDirectionY;
  float tMaxY = (maxCorner_.y - ray.getOrigin().y) * invDirectionY;
  if (tMinY > tMaxY) {
    std::swap(tMinY, tMaxY);
  }

  if (tMinY > intersectionIntervalMin) {
    intersectionIntervalMin = tMinY;
  }
  if (tMaxY < intersectionIntervalMax) {
    intersectionIntervalMax = tMaxY;
  }
  if (intersectionIntervalMin > intersectionIntervalMax) {
    return false;
  }

  // z
  const float invDirectionZ = 1.0f / ray.getDirection().z;
  float tMinZ = (minCorner_.z - ray.getOrigin().z) * invDirectionZ;
  float tMaxZ = (maxCorner_.z - ray.getOrigin().z) * invDirectionZ;
  if (tMinZ > tMaxZ) {
    std::swap(tMinZ, tMaxZ);
  }

  if (tMinZ > intersectionIntervalMin) {
    intersectionIntervalMin = tMinZ;
  }
  if (tMaxZ < intersectionIntervalMax) {
    intersectionIntervalMax = tMaxZ;
  }
  if (intersectionIntervalMin > intersectionIntervalMax) {
    return false;
  }

  return true;
}