#ifndef SCENE_HPP
#define SCENE_HPP

#include <memory>
#include <optional>
#include <vector>

#include "Color.hpp"
#include "Environment.hpp"

class Object;
class SurfaceInfo;
class Ray;
class Light;

class Scene {
 public:
  Scene(std::unique_ptr<Environment> environment)
      : objects_(), lights_(), environment_(std::move(environment)) {}

  std::shared_ptr<Object> intersects(const Ray& ray, float& t, SurfaceInfo& surfaceInfo) const;
  bool occludes(const Ray& ray, float maxT) const;

  const Environment& getEnvironment() const { return *environment_; };
  std::vector<std::shared_ptr<Light>> getLights() const { return lights_; }

  void addObject(std::shared_ptr<Object> object);
  void addLight(std::shared_ptr<Light> light);

 private:
  std::vector<std::shared_ptr<Object>> objects_;
  std::vector<std::shared_ptr<Light>> lights_;
  std::unique_ptr<Environment> environment_;
};

#endif