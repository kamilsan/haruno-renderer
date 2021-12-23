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

Color PathTracer::integrate(const Ray& cameraRay, const Scene& scene, RNG& rng) {
  Ray ray = cameraRay;
  Color coef{1.0};
  Color result{};
  SurfaceInfo surfaceInfo{};
  std::shared_ptr<Object> object = nullptr;
  bool raySpecular = false;

  for (unsigned int i = 0;; ++i) {
    Color color{};
    float t = -1;
    object = scene.intersects(ray, t, surfaceInfo);

    if ((i == 0 || raySpecular) && surfaceInfo.emittance) {
      return coef * surfaceInfo.emittance.value();
    }

    if (object) {
      const auto position = ray(t);
      const auto& normal = surfaceInfo.normal;
      const auto& uv = surfaceInfo.uv;
      const auto& material = object->getMaterial();
      const auto& brdf = material.getBRDF();
      const auto albedo = material.getAlbedo(uv);
      const auto wo = (ray.getOrigin() - position).normalized();

      for (const auto& light : scene.getLights()) {
        if (light->isDelta()) {
          const auto Li = light->evaluate(position);
          float maxT = -1;
          const auto shadowRay = light->getShadowRay(position, maxT);
          const auto wi = shadowRay.getDirection();

          const auto occlusion = scene.occludes(shadowRay, maxT);

          if (!occlusion) {
            const auto f = brdf.evaluate(wi, wo);
            const auto coswi = std::max(wi.dot(normal), 0.0f);
            color += f * coswi * Li * albedo;
          }
        } else {
          Vector3f lightSample;
          SurfaceInfo lightSurfaceInfo;
          float pdf = 1.0f;
          const auto Le = light->sampleLe(lightSample, lightSurfaceInfo, rng, pdf);
          auto toLight = lightSample - position;
          const auto lengthSq = toLight.lengthSq();
          const auto maxT = std::sqrt(lengthSq);
          toLight /= maxT;

          const Ray shadowRay{position + toLight * 0.001f, toLight};
          const auto occluded = scene.occludes(shadowRay, maxT * 0.99f);

          if (!occluded) {
            const auto lightNormal = lightSurfaceInfo.normal;
            const auto cosLight = std::max(0.0f, -toLight.dot(lightNormal));
            const auto cosSurface = std::max(0.0f, toLight.dot(normal));
            const auto attenuation = 1.0f / lengthSq;
            const auto f = brdf.evaluate(toLight, wo);
            color += albedo * f * Le * cosLight * cosSurface * attenuation / pdf;
          }
        }
      }

      result += coef * color;

      Vector3f tangent, bitangent;
      createOrthogonalFrame(normal, tangent, bitangent);
      const auto woShading = transformFromTangentSpace(wo, normal, tangent, bitangent);

      Vector3f sample{};
      float pdf = 1.0f;
      const float f = brdf.sample(woShading, rng, sample, pdf);
      const float coswi = std::max(sample.y, 0.0f);  // wi . (0, 1, 0)

      coef *= albedo * f * coswi / pdf;
      raySpecular = brdf.getType() == BRDF::Type::PerfectSpecular;

      Vector3f wi = transformToTangentSpace(sample, normal, tangent, bitangent);
      ray = Ray{position + wi * 0.001f, wi};

      if (i > 3) {
        const float maxComponent = std::max(coef.r, std::max(coef.g, coef.b));
        const float survivalProbability = std::max(0.1f, 1.0f - maxComponent);
        if (rng.get() < survivalProbability) {
          break;
        }
        coef /= (1.0f - survivalProbability);
      }
    } else {
      result += coef * scene.getEnvironment().getColor(ray.getDirection());
      break;
    }
  }

  return result;
}
