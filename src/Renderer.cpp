#include "Renderer.hpp"
#include "Vector.hpp"
#include "Ray.hpp"
#include "Camera.hpp"
#include "Material.hpp"
#include "Scene.hpp"
#include "Object.hpp"
#include "Environment.hpp"
#include "Light.hpp"
#include "BRDF.hpp"
#include "Math.hpp"

#include <iostream>

Image Renderer::render(std::unique_ptr<Camera> camera, const Scene& scene) const
{
  Image result{width_, height_};

  const float aspectRatio = static_cast<float>(width_) / height_;

  for(int y = 0; y < height_; ++y)
  {
    for(int x = 0; x < width_; ++x)
    {
      Color color{};
      for(unsigned int i = 0; i < samples_; ++i)
      {
        const float ndcX = aspectRatio * (2.0f * ((x + rng_.get()) / (width_ - 1.0f)) - 1.0f);
        const float ndcY = -2.0f * ((y + rng_.get()) / (height_ - 1.0f)) + 1.0f;

        const Ray primaryRay = camera->getCameraRay(ndcX, ndcY, rng_);
        color += rayTrace(primaryRay, scene, depth_);
      }

      color /= samples_;

      result.setPixel(x, y, color);
    }
    std::cout << "Rendering... " << 100.f * y / (height_ - 1.0f) << "%\n";
  }

  return result;
}

Color Renderer::rayTrace(const Ray& ray, const Scene& scene, int depth) const
{
  if(depth < 0)
    return Color{};

  float t = -1;
  auto object = scene.intersects(ray, t);

  if(object)
  {
    Color color{};
    const auto position = ray(t);
    const auto normal = object->getNormal(position);
    const auto& material = object->getMaterial();
    const auto albedo = material.getAlbedo();
    const auto wo = (ray.getOrigin() - position).normalized();

    for(const auto& light : scene.getLights())
    {
      const auto Li = light->evaluate(position);
      float maxT = -1;
      const auto shadowRay = light->getShadowRay(position, maxT);
      const auto wi = shadowRay.getDirection();

      const auto occlusion = scene.occludes(shadowRay, maxT);

      if(!occlusion)
      {
        const auto f = material.getBRDF().evaluate(wi, wo);
        const auto coswi = std::abs(wi.dot(normal));
        color += f * coswi * Li * albedo;
      }
    }

    Vector tangent, bitangent;
    createOrthogonalFrame(normal, tangent, bitangent);
    const auto wo_shading = transformFromTangentSpace(wo, normal, tangent, bitangent);
    
    Vector sample{};
    float pdf = 1.0f;
    const float f = material.getBRDF().sample(wo_shading, rng_, sample, pdf);
    const float coswi = std::fabs(sample.y); // wi . (0, 1, 0)

    Vector wi = transformToTangentSpace(sample, normal, tangent, bitangent);

    const Ray secondaryRay{position + wi * 0.0001f, wi}; 
    Color Li = rayTrace(secondaryRay, scene, depth - 1);
    color += albedo * Li * f * coswi / pdf;

    return color;
  }
  else
  {
    return scene.getEnvironment().getColor(ray.getDirection());
  }
}