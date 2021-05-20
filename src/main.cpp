#include "Renderer.hpp"
#include "PinholeCamera.hpp"
#include "Sphere.hpp"
#include "Scene.hpp"
#include "SolidMaterial.hpp"

int main()
{
  Renderer renderer{1920, 1080};
  
  auto camera = std::make_unique<PinholeCamera>();
  
  Scene scene{};

  auto material1 = std::make_shared<SolidMaterial>(Color{1.0, 0.5, 1.0});
  auto material2 = std::make_shared<SolidMaterial>(Color{0.5, 1.0, 1.0});

  scene.addObject(std::make_shared<Sphere>(Vector{0, 0, 1}, 0.5f, material1));
  scene.addObject(std::make_shared<Sphere>(Vector{1, 0, 2}, 0.5f, material2));

  const Image render = renderer.render(std::move(camera), scene);

  render.save("render.ppm");

  return 0;
}