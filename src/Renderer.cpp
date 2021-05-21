#include "Renderer.hpp"
#include "Vector.hpp"
#include "Ray.hpp"
#include "Camera.hpp"
#include "Material.hpp"
#include "Scene.hpp"
#include "Object.hpp"
#include "Environment.hpp"
#include "Light.hpp"

#include <cmath>

Image Renderer::render(std::unique_ptr<Camera> camera, const Scene& scene) const
{
  Image result{width_, height_};

  const float aspectRatio = static_cast<float>(width_) / height_;

  for(int y = 0; y < height_; ++y)
  {
    for(int x = 0; x < width_; ++x)
    {
      const float ndcX = aspectRatio * (2.0f * ((x + 0.5f) / (width_ - 1.0f)) - 1.0f);
      const float ndcY = -2.0f * ((y + 0.5f) / (height_ - 1.0f)) + 1.0f;

      const Ray primaryRay = camera->getCameraRay(ndcX, ndcY);

      const Color color = rayTrace(primaryRay, scene);

      result.setPixel(x, y, color);
    }
  }

  return result;
}

Color Renderer::rayTrace(const Ray& ray, const Scene& scene) const
{
  float t = -1;
  auto object = scene.intersects(ray, t);

  if(object)
  {
    Color color{};
    const auto position = ray(t);
    const auto normal = object->getNormal(position);
    const auto& material = object->getMaterial();
    const auto albedo = material.getAlbedo();

    for(const auto& light : scene.getLights())
    {
      const auto Li = light->evaluate(position);
      float maxT = -1;
      const auto shadowRay = light->getShadowRay(position, maxT);

      const auto occlusion = scene.occludes(shadowRay, maxT);

      if(!occlusion)
        color += Li * albedo;
    }

    return color;
  }
  else
  {
    return scene.getEnvironment().getColor(ray.getDirection());
  }
}