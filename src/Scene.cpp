#include "Scene.hpp"

#include "Light.hpp"
#include "Object.hpp"

std::shared_ptr<Object> Scene::intersects(const Ray& ray, float& t,
                                          SurfaceInfo& surfaceInfo) const {
  float minT = -1;
  std::shared_ptr<Object> result = nullptr;
  SurfaceInfo tempSurfaceInfo;

  for (const auto& obj : objects_) {
    const auto candidate = obj->intersects(ray, tempSurfaceInfo);
    if (candidate > 0 && (minT < 0 || candidate < minT)) {
      minT = candidate;
      result = obj;
      surfaceInfo = tempSurfaceInfo;
    }
  }

  t = minT;
  return result;
}

std::optional<Color> Scene::intersectsLight(const Ray& ray, float& t) const {
  std::optional<Color> result{};

  float minT = -1;
  SurfaceInfo surfaceInfo;
  for (const auto& light : lights_) {
    const auto candidate = light->intersects(ray, surfaceInfo);
    if (candidate > 0 && (minT < 0 || candidate < minT)) {
      minT = candidate;
      result = light->evaluate(ray(candidate));
    }
  }

  t = minT;
  return result;
}

bool Scene::occludes(const Ray& ray, float maxT) const {
  SurfaceInfo surfaceInfo{};
  for (const auto& obj : objects_) {
    const auto candidate = obj->intersects(ray, surfaceInfo);
    if (candidate > 0 && (candidate < maxT || maxT < 0)) return true;
  }

  return false;
}

void Scene::addObject(std::shared_ptr<Object> object) { objects_.emplace_back(std::move(object)); }

void Scene::addLight(std::shared_ptr<Light> light) { lights_.emplace_back(std::move(light)); }