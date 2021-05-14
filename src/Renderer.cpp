#include "Renderer.hpp"
#include "Vector.hpp"
#include "Ray.hpp"
#include "Sphere.hpp"
#include "Camera.hpp"

#include <cmath>

Image Renderer::render(std::unique_ptr<Camera> camera, int width, int height) const
{
  Image result{width, height};

  const float aspectRatio = static_cast<float>(width) / height;

  for(int y = 0; y < height; ++y)
  {
    for(int x = 0; x < width; ++x)
    {
      const float ndcX = aspectRatio * (2.0f * ((x + 0.5f) / (width - 1.0f)) - 1.0f);
      const float ndcY = -2.0f * ((y + 0.5f) / (height - 1.0f)) + 1.0f;

      const Ray primaryRay = camera->getCameraRay(ndcX, ndcY);

      const Color color = rayTrace(primaryRay);

      result.setPixel(x, y, color);
    }
  }

  return result;
}

Color Renderer::rayTrace(const Ray& ray) const
{
  // Temporary code
  const Sphere sphere{Vector{0, 0, 1}, 0.5f};
  const float t = sphere.intersects(ray);

  const float phi = std::atan(ray.getDirection().y / ray.getDirection().z);
  if(t > 0.0f)
    return Color{1.0f};
  else
  {
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