#include "Scene.hpp"

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