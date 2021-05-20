#include "Renderer.hpp"
#include "PinholeCamera.hpp"
#include "Sphere.hpp"
#include "Plane.hpp"
#include "Scene.hpp"
#include "SolidMaterial.hpp"
#include "SimpleEnvironment.hpp"

#include <memory>

int main()
{
  Renderer renderer{1920, 1080};
  
  auto camera = std::make_unique<PinholeCamera>();
  
  const Color zenith{0.176f, 0.557f, 0.988f};
  const Color horizon{0.71f, 0.259f, 0.149f};
  const Color ground{0.467f, 0.384f, 0.325f};
  auto environment = std::make_unique<SimpleEnvironment>(zenith, horizon, ground); 

  Scene scene{std::move(environment)};

  auto material1 = std::make_shared<SolidMaterial>(Color{1.0, 0.5, 1.0});
  auto material2 = std::make_shared<SolidMaterial>(Color{0.5, 1.0, 1.0});
  auto material3 = std::make_shared<SolidMaterial>(Color{0.9, 0.9, 0.9});

  scene.addObject(std::make_shared<Sphere>(Vector{0, 0, 1}, 0.5f, material1));
  scene.addObject(std::make_shared<Sphere>(Vector{1, 0, 2}, 0.5f, material2));
  scene.addObject(std::make_shared<Plane>(Vector{0, -0.5, 2}, Vector{0, 1, 0}, material3));

  const Image render = renderer.render(std::move(camera), scene);

  render.save("render.ppm");

  return 0;
}