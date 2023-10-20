#include "DirectLighting.hpp"

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

Color DirectLighting::integrate(const Ray& cameraRay, const Scene& scene, RNG& rng) const {
  Ray ray = cameraRay;
  Color coeff{1.0};
  Color result{};
  SurfaceInfo surfaceInfo{};
  std::shared_ptr<Object> object = nullptr;

  for (size_t i = 0; i < maxDepth_; ++i) {
    Color color{};
    Float t = -1;
    object = scene.intersects(ray, t, surfaceInfo);

    if (surfaceInfo.emittance) {
      return coeff * surfaceInfo.emittance.value();
    }

    if (object) {
      const auto position = ray(t);
      const auto& normal = surfaceInfo.normal;
      const auto& uv = surfaceInfo.uv;
      const auto& material = object->getMaterial();
      const auto& brdf = material.getBRDF();
      const auto albedo = material.getAlbedo(uv);
      const auto wo = -ray.getDirection();

      const auto isSpecular = brdf.getType() == BRDF::Type::PerfectSpecular;

      if (!isSpecular) {
        const auto directLighting =
            computeDirectLighting(scene, position, wo, surfaceInfo, material, rng);
        result += coeff * directLighting;
      }

      if (isSpecular) {
        Vector3t tangent, bitangent;
        createOrthogonalFrame(normal, tangent, bitangent);
        const auto woShading = transformFromTangentSpace(wo, normal, tangent, bitangent);

        Vector3t sample{};
        Float pdf = 1.0;
        const Float f = brdf.sample(woShading, rng, sample, pdf);
        const Float coswi = std::max(sample.y, static_cast<Float>(0.0));  // wi . (0, 1, 0)

        coeff *= albedo * f * coswi / pdf;

        Vector3t wi = transformToTangentSpace(sample, normal, tangent, bitangent).normalized();
        ray = Ray{position + wi * 0.001, wi};
      } else {
        break;
      }
    } else {
      result += coeff * scene.getEnvironment().getColor(ray.getDirection());
      break;
    }
  }

  return result;
}
