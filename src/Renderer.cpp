#include "Renderer.hpp"
#include "Vector.hpp"
#include "Ray.hpp"
#include "Camera.hpp"
#include "Material.hpp"
#include "Scene.hpp"
#include "Object.hpp"

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
    const auto& material = object->getMaterial();
    return material.getAlbedo();
  }
  else
  {
    const float phi = std::atan(ray.getDirection().y / ray.getDirection().z);
    if(phi < 0)
      return Color{0.467f, 0.384f, 0.325f};
    else
    {
      const Color top{0.176f, 0.557f, 0.988f};
      const Color horizon{0.71f, 0.259f, 0.149f};

      const float lerpFactor = std::pow(phi / M_PI_2, 1/2.5f);
      const Color sky = lerpFactor * top + (1.0f - lerpFactor) * horizon;

      return sky;
    }
  }
}