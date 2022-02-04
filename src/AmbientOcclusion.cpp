#include "AmbientOcclusion.hpp"

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

Color AmbientOcclusion::integrate(const Ray& cameraRay, const Scene& scene, RNG& rng) const {
  SurfaceInfo surfaceInfo{};
  std::shared_ptr<Object> object = nullptr;

  float t = -1;
  object = scene.intersects(cameraRay, t, surfaceInfo);

  if (object) {
    const auto position = cameraRay(t);
    const auto& normal = surfaceInfo.normal;

    Vector3f tangent, bitangent;
    createOrthogonalFrame(normal, tangent, bitangent);

    Vector3f sampleShading = rng.sampleHemisphereCosineWeighted();
    Vector3f sample = transformToTangentSpace(sampleShading, normal, tangent, bitangent);
    const Ray sampleRay{position + sample * 0.001f, sample};
    const auto occluded = scene.occludes(sampleRay, radius_);
    if (!occluded) {
      return Color{1.0};
    } else {
      return Color{};
    }
  }

  return Color{1.0f};
}
