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

Color DirectLighting::integrate(const Ray& cameraRay, const Scene& scene, RNG& rng) {
  Ray ray = cameraRay;
  Color coef{1.0};
  Color result{};
  SurfaceInfo surfaceInfo{};
  std::shared_ptr<Object> object = nullptr;

  for (size_t i = 0; i < maxDepth_; ++i) {
    float t = -1;
    object = scene.intersects(ray, t, surfaceInfo);

    if (object) {
      Color color{};
      const auto position = ray(t);
      const auto& normal = surfaceInfo.normal;
      const auto& uv = surfaceInfo.uv;
      const auto& material = object->getMaterial();
      const auto albedo = material.getAlbedo(uv);
      const auto wo = (ray.getOrigin() - position).normalized();

      for (const auto& light : scene.getLights()) {
        const auto Li = light->evaluate(position);
        float maxT = -1;
        const auto shadowRay = light->getShadowRay(position, maxT);
        const auto wi = shadowRay.getDirection();

        const auto occlusion = scene.occludes(shadowRay, maxT);

        if (!occlusion) {
          const auto f = material.getBRDF().evaluate(wi, wo);
          const auto coswi = std::max(wi.dot(normal), 0.0f);
          color += f * coswi * Li * albedo;
        }
      }

      result += coef * color;

      if (material.getBRDF().getType() == BRDF::Type::PerfectSpecular) {
        Vector3f tangent, bitangent;
        createOrthogonalFrame(normal, tangent, bitangent);
        const auto woShading = transformFromTangentSpace(wo, normal, tangent, bitangent);

        Vector3f sample{};
        float pdf = 1.0f;
        const float f = material.getBRDF().sample(woShading, rng, sample, pdf);
        const float coswi = std::max(sample.y, 0.0f);  // wi . (0, 1, 0)

        coef *= albedo * f * coswi / pdf;

        Vector3f wi = transformToTangentSpace(sample, normal, tangent, bitangent);
        ray = Ray{position + wi * 0.0001f, wi};
      } else {
        break;
      }
    } else {
      result += coef * scene.getEnvironment().getColor(ray.getDirection());
      break;
    }
  }

  return result;
}
