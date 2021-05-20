#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <memory>

class Object;
class Ray;

class Scene
{
public:
  Scene(): objects_() {}

  std::shared_ptr<Object> intersects(const Ray& ray, float& t) const;

  void addObject(std::shared_ptr<Object> object);

private:
  std::vector<std::shared_ptr<Object>> objects_;
};

#endif