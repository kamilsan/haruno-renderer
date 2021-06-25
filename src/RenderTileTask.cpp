#include "RenderTileTask.hpp"
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
#include "ThreadPool.hpp"

RenderTileTask::RenderTileTask(int width, int height, unsigned int samples, unsigned int depth, 
  ImageTile tile, const Camera& camera, const Scene& scene, RNG rng): 
  width_(width), height_(height), samples_(samples), depth_(depth), 
  tile_(std::move(tile)), camera_(camera), scene_(scene), rng_(std::move(rng))
{
  aspectRatio_ = static_cast<float>(width) / height;
}

void RenderTileTask::renderTile(ImageTile& tile, const Camera& camera, const Scene& scene, RNG rng) const
{
  for(unsigned int tileY = 0; tileY < tile.getHeight(); ++tileY)
  {
    for(unsigned int tileX = 0; tileX < tile.getWidth(); ++tileX)
    {
      const unsigned int x = tile.getMinX() + tileX;
      const unsigned int y = tile.getMinY() + tileY;

      Color color{};
      for(unsigned int i = 0; i < samples_; ++i)
      {
        const float ndcX = aspectRatio_ * (2.0f * ((x + rng_.get()) / (width_ - 1.0f)) - 1.0f);
        const float ndcY = -2.0f * ((y + rng_.get()) / (height_ - 1.0f)) + 1.0f;

        const Ray primaryRay = camera.getCameraRay(ndcX, ndcY, rng_);
        color += rayTrace(primaryRay, scene, depth_, rng);
      }

      color /= samples_;

      tile.setPixel(tileX, tileY, color);
    }
  }
}

Color RenderTileTask::rayTrace(const Ray& ray, const Scene& scene, int depth, RNG& rng) const
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
    Color Li = rayTrace(secondaryRay, scene, depth - 1, rng);
    color += albedo * Li * f * coswi / pdf;

    return color;
  }
  else
  {
    return scene.getEnvironment().getColor(ray.getDirection());
  }
}