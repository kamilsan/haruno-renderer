#include "DebugIntegrator.hpp"

#include "BRDF.hpp"
#include "Camera.hpp"
#include "Environment.hpp"
#include "Light.hpp"
#include "Material.hpp"
#include "Math.hpp"
#include "Object.hpp"
#include "RNG.hpp"
#include "Ray.hpp"
#include "Scene.hpp"
#include "Vector3.hpp"

Color DebugIntegrator::integrate(const Ray& cameraRay, const Scene& scene, RNG&) const {
  SurfaceInfo surfaceInfo{};

  Float t = -1;
  std::shared_ptr<Object> object = scene.intersects(cameraRay, t, surfaceInfo);

  if (object) {
    Color color{};
    const auto position = cameraRay(t);
    const auto& normal = surfaceInfo.normal;
    const auto& uv = surfaceInfo.uv;
    const auto& material = object->getMaterial();
    const auto albedo = material.getAlbedo(uv);

    if (outputType_ == OutputType::Albedo) {
      return albedo;
    } else if (outputType_ == OutputType::Normal) {
      const Vector3t color = (normal + Vector3t(1.0, 1.0, 1.0)) * 0.5;
      return Color{color.x, color.y, color.z};
    } else if (outputType_ == OutputType::Depth) {
      return Color{1.0} * position.z;
    }
  }

  return Color{};
}
