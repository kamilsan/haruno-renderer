#include "Integrator.hpp"

#include "Color.hpp"
#include "Light.hpp"
#include "Material.hpp"
#include "Object.hpp"
#include "Scene.hpp"
#include "Vector3.hpp"

Color Integrator::computeDirectLighting(const Scene& scene, const Vector3f& position,
                                        const Vector3f& wo, const SurfaceInfo& surfaceInfo,
                                        const Material& material, RNG& rng) const {
  Color result{};

  const auto& normal = surfaceInfo.normal;
  const auto& uv = surfaceInfo.uv;
  const auto& brdf = material.getBRDF();
  const auto albedo = material.getAlbedo(uv);

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
        result += f * coswi * Li * albedo;
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
        result += albedo * f * Le * cosLight * cosSurface * attenuation / pdf;
      }
    }
  }

  return result;
}