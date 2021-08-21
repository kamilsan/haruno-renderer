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

  for (unsigned int i = 0;; ++i) {
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

      Vector3f tangent, bitangent;
      createOrthogonalFrame(normal, tangent, bitangent);
      const auto woShading = transformFromTangentSpace(wo, normal, tangent, bitangent);

      Vector3f sample{};
      float pdf = 1.0f;
      const float f = material.getBRDF().sample(woShading, rng, sample, pdf);
      const float coswi = std::max(sample.y, 0.0f);  // wi . (0, 1, 0)

      result += coef * color;
      coef *= albedo * f * coswi / pdf;

      Vector3f wi = transformToTangentSpace(sample, normal, tangent, bitangent);
      ray = Ray{position + wi * 0.0001f, wi};

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

/*

Color RenderTileTask::rayTrace(const Ray& camera_ray) const {
  Ray ray = camera_ray;
  Color coef{1.0};
  Color result{};
  std::shared_ptr<Object> object = nullptr;
  bool primary_or_specular = true;

  for (unsigned int i = 0;; ++i) {
    float t = -1;

    if (primary_or_specular) {
      const auto Le = scene_.intersectsLight(ray, t);

      if (Le.has_value()) {
        result += coef * Le.value();
        break;
      }
    }

    object = scene_.intersects(ray, t);

    if (object) {
      Color color{};
      const auto position = ray(t);
      const auto surfaceInfo = object->getSurfaceInfo(position);
      const auto& normal = surfaceInfo.normal;
      const auto& uv = surfaceInfo.uv;
      const auto& material = object->getMaterial();
      const auto albedo = material.getAlbedo(uv.first, uv.second);
      const auto wo = (ray.getOrigin() - position).normalized();

      for (const auto& light : scene_.getLights()) {
        if (light->isDelta()) {
          const auto Li = light->evaluate(position);
          float maxT = -1;
          const auto shadowRay = light->getShadowRay(position, maxT);
          const auto wi = shadowRay.getDirection();

          const auto occluded = scene_.occludes(shadowRay, maxT);

          if (!occluded) {
            const auto f = material.getBRDF().evaluate(wi, wo);
            const auto coswi = std::max(0.0f, wi.dot(normal));
            color += f * coswi * Li * albedo;
          }
        } else {
          Color emittance = {};
          for (unsigned int n = 0; n < lightSamples_; ++n) {
            Vector lightSample;
            const auto Le = light->sampleLe(lightSample, rng_);
            auto toLight = lightSample - position;
            const auto lengthSq = toLight.lengthSq();
            const auto maxT = std::sqrt(lengthSq);
            toLight /= maxT;

            toLight = toLight.normalized();
            const Ray shadowRay{position + toLight * 0.001f, toLight};
            const auto occluded = scene_.occludes(shadowRay, maxT * 0.999f);

            if (!occluded) {
              const auto lightNormal = light->getNormalAt(lightSample);
              const auto cosLight = std::max(0.0f, (-toLight).dot(lightNormal));
              const auto cosSurface = std::max(0.0f, toLight.dot(normal));
              const auto attenuation = 1.0f / lengthSq;
              const auto f = material.getBRDF().evaluate(toLight, wo);
              emittance += f * Le * cosLight * cosSurface * attenuation;
            }
          }
          color += albedo * emittance / (lightSamples_ * light->pdf());
        }
      }

      Vector tangent, bitangent;
      createOrthogonalFrame(normal, tangent, bitangent);
      const auto woShading = transformFromTangentSpace(wo, normal, tangent, bitangent);

      Vector sample{};
      float pdf = 1.0f;
      const float f = material.getBRDF().sample(woShading, rng_, sample, pdf);
      const float coswi = std::max(0.0f, sample.y);  // wi . (0, 1, 0)
      primary_or_specular = pdf == 1.0f;

      result += coef * color;
      coef *= albedo * f * coswi / pdf;

      Vector wi = transformToTangentSpace(sample, normal, tangent, bitangent);
      ray = Ray{position + wi * 0.0001f, wi};

      if (i > 3) {
        const float maxComponent = std::max(coef.r, std::max(coef.g, coef.b));
        const float survivalProbability = std::max(0.1f, 1.0f - maxComponent);
        if (rng_.get() < survivalProbability) {
          break;
        }
        coef /= (1.0f - survivalProbability);
      }
    } else {
      result += coef * scene_.getEnvironment().getColor(ray.getDirection());
      break;
    }
  }

  return result;
}

*/
