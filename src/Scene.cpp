#include "Scene.hpp"

#include "Object.hpp"

std::shared_ptr<Object> Scene::intersects(const Ray& ray, float& t) const
{
  float minT = -1;
  std::shared_ptr<Object> result = nullptr;
  for(const auto& obj : objects_)
  {
    const auto candidate = obj->intersects(ray);
    if(candidate > 0 && (minT < 0 || candidate < minT))
    {
      minT = candidate;
      result = obj;
    }
  } 

  t = minT;
  return result;
}

void Scene::addObject(std::shared_ptr<Object> object)
{
  objects_.emplace_back(std::move(object));
}