#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <memory>

#include "Environment.hpp"

class Object;
class Ray;

class Scene
{
public:
  Scene(std::unique_ptr<Environment> environment): 
    objects_(), environment_(std::move(environment)) {}

  std::shared_ptr<Object> intersects(const Ray& ray, float& t) const;
  const Environment& getEnvironment() const { return *environment_; };

  void addObject(std::shared_ptr<Object> object);

private:
  std::vector<std::shared_ptr<Object>> objects_;
  std::unique_ptr<Environment> environment_;
};

#endif