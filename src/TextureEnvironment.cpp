#include "TextureEnvironment.hpp"

#include "Math.hpp"
#include "Vector3.hpp"

Color TextureEnvironment::getColor(const Vector3t& direction) const {
  Float theta = PI - std::acos(direction.y);
  Float phi = std::atan2(direction.x, direction.z);
  Float u = std::max(0.0, std::min(1.0, phi * 0.5 * ONE_OVER_PI + 0.5));
  Float v = std::max(0.0, std::min(1.0, theta * ONE_OVER_PI));

  return texture_->get(Vector2t(u, v));
}