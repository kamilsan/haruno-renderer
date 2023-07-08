#include "PathTracer.hpp"

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

Color PathTracer::integrate(const Ray& cameraRay, const Scene& scene, RNG& rng) const {
  Ray ray = cameraRay;
  Color coeff{1.0};
  Color result{};
  SurfaceInfo surfaceInfo{};
  std::shared_ptr<Object> object = nullptr;
  bool raySpecular = false;

  for (unsigned int i = 0;; ++i) {
    float t = -1;
    object = scene.intersects(ray, t, surfaceInfo);

    if ((i == 0 || raySpecular) && surfaceInfo.emittance) {
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

      const auto directLighting =
          computeDirectLighting(scene, position, wo, surfaceInfo, material, rng);
      result += coeff * directLighting;

      Vector3f tangent, bitangent;
      createOrthogonalFrame(normal, tangent, bitangent);
      const auto woShading = transformFromTangentSpace(wo, normal, tangent, bitangent);

      Vector3f sample{};
      float pdf = 1.0f;
      const float f = brdf.sample(woShading, rng, sample, pdf);
      const float coswi = std::max(sample.y, 0.0f);  // wi . (0, 1, 0)

      coeff *= albedo * f * coswi / pdf;
      raySpecular = brdf.getType() == BRDF::Type::PerfectSpecular;

      Vector3f wi = transformToTangentSpace(sample, normal, tangent, bitangent).normalized();
      ray = Ray{position + wi * 0.001f, wi};

      if (i > 3) {
        const float maxComponent = std::max(coeff.r, std::max(coeff.g, coeff.b));
        const float terminationProbability = std::max(0.1f, 1.0f - maxComponent);
        if (rng.get() < terminationProbability) {
          break;
        }
        coeff /= (1.0f - terminationProbability);
      }
    } else {
      result += coeff * scene.getEnvironment().getColor(ray.getDirection());
      break;
    }
  }

  return result;
}
