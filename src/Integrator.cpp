#include "Integrator.hpp"

#include "Color.hpp"
#include "Light.hpp"
#include "Material.hpp"
#include "Object.hpp"
#include "Scene.hpp"
#include "Vector3.hpp"

Color Integrator::computeDirectLighting(const Scene& scene, const Vector3t& position,
                                        const Vector3t& wo, const SurfaceInfo& surfaceInfo,
                                        const Material& material, RNG& rng) const {
  Color result{};

  const auto& normal = surfaceInfo.normal;
  const auto& uv = surfaceInfo.uv;
  const auto& brdf = material.getBRDF();
  const auto albedo = material.getAlbedo(uv);

  for (const auto& light : scene.getLights()) {
    if (light->isDelta()) {
      const auto Li = light->evaluate(position);
      Float maxT = -1;
      const auto shadowRay = light->getShadowRay(position, maxT);
      const auto wi = shadowRay.getDirection();

      const auto occlusion = scene.occludes(shadowRay, maxT);

      if (!occlusion) {
        const auto f = brdf.evaluate(wi, wo);
        const auto coswi = std::max(wi.dot(normal), static_cast<Float>(0.0));
        result += f * coswi * Li * albedo;
      }
    } else {
      Vector3t lightSample;
      SurfaceInfo lightSurfaceInfo;
      Float pdf = 1.0;
      const auto Le = light->sampleLe(lightSample, lightSurfaceInfo, rng, pdf);
      auto toLight = lightSample - position;
      const auto lengthSq = toLight.lengthSq();
      const auto maxT = std::sqrt(lengthSq);
      toLight /= maxT;

      const Ray shadowRay{position + toLight * 0.001, toLight};
      const auto occluded = scene.occludes(shadowRay, maxT * 0.99);

      if (!occluded) {
        const auto lightNormal = lightSurfaceInfo.normal;
        const auto cosLight = std::max(static_cast<Float>(0.0), -toLight.dot(lightNormal));
        const auto cosSurface = std::max(static_cast<Float>(0.0), toLight.dot(normal));
        const auto attenuation = 1.0 / lengthSq;
        const auto f = brdf.evaluate(toLight, wo);
        result += albedo * f * Le * cosLight * cosSurface * attenuation / pdf;
      }
    }
  }

  return result;
}