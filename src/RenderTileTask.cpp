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

void RenderTileTask::renderTile()
{
  for(unsigned int tileY = 0; tileY < tile_.getHeight(); ++tileY)
  {
    for(unsigned int tileX = 0; tileX < tile_.getWidth(); ++tileX)
    {
      const unsigned int x = tile_.getMinX() + tileX;
      const unsigned int y = tile_.getMinY() + tileY;

      Color color{};
      for(unsigned int i = 0; i < samples_; ++i)
      {
        const float ndcX = aspectRatio_ * (2.0f * ((x + rng_.get()) / (width_ - 1.0f)) - 1.0f);
        const float ndcY = -2.0f * ((y + rng_.get()) / (height_ - 1.0f)) + 1.0f;

        const Ray primaryRay = camera_.getCameraRay(ndcX, ndcY, rng_);
        color += rayTrace(primaryRay);
      }

      color /= samples_;

      tile_.setPixel(tileX, tileY, color);
    }
  }
}

Color RenderTileTask::rayTrace(const Ray& camera_ray) const
{
  Ray ray = camera_ray;
  Color coef{1.0};
  Color result{};
  std::shared_ptr<Object> object = nullptr;

  for(unsigned int i = 0; i <= depth_; ++i)
  {
    float t = -1;
    object = scene_.intersects(ray, t);

    if(object)
    {
      Color color{};
      const auto position = ray(t);
      const auto surfaceInfo = object->getSurfaceInfo(position);
      const auto& normal = surfaceInfo.normal;
      const auto& uv = surfaceInfo.uv;
      const auto& material = object->getMaterial();
      const auto albedo = material.getAlbedo(uv.first, uv.second);
      const auto wo = (ray.getOrigin() - position).normalized();

      for(const auto& light : scene_.getLights())
      {
        const auto Li = light->evaluate(position);
        float maxT = -1;
        const auto shadowRay = light->getShadowRay(position, maxT);
        const auto wi = shadowRay.getDirection();

        const auto occlusion = scene_.occludes(shadowRay, maxT);

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

      result += coef * color;
      coef *= albedo * f * coswi / pdf;

      Vector wi = transformToTangentSpace(sample, normal, tangent, bitangent);
      ray = Ray{position + wi * 0.0001f, wi}; 
    }
    else
    {
      result += coef * scene_.getEnvironment().getColor(ray.getDirection());
      break;
    }
  }

  return result;
}