#include "Renderer.hpp"
#include "PinholeCamera.hpp"
#include "SimpleCamera.hpp"
#include "Sphere.hpp"
#include "Plane.hpp"
#include "Rectangle.hpp"
#include "Scene.hpp"
#include "SolidMaterial.hpp"
#include "MirrorMaterial.hpp"
#include "SimpleEnvironment.hpp"
#include "DirectionalLight.hpp"
#include "PointLight.hpp"

#include <chrono>
#include <memory>

int main()
{
  Renderer renderer{1920, 1080, 256, 3};
  
  auto camera = std::make_unique<SimpleCamera>(90.0f, 0.01f, 2.0f, Vector{0, 0, -1}, Vector{0, 0, 1}, Vector{0, 1, 0});
  
  const Color zenith{0.176f, 0.557f, 0.988f};
  const Color horizon{0.71f, 0.259f, 0.149f};
  const Color ground{0.467f, 0.384f, 0.325f};
  auto environment = std::make_unique<SimpleEnvironment>(zenith, horizon, ground); 

  Scene scene{std::move(environment)};

  auto materialWallRed = std::make_shared<SolidMaterial>(Color{0.9f, 0.1f, 0.05f}, 0.6f);
  auto materialWallGreen = std::make_shared<SolidMaterial>(Color{0.1f, 0.9f, 0.05f}, 0.6f);
  auto materialGround = std::make_shared<SolidMaterial>(Color{1.0f, 1.0f, 1.0f}, 0.6f);
  auto materialMirror = std::make_shared<MirrorMaterial>(Color{1.0f, 1.0f, 1.0f});

  scene.addLight(std::make_shared<PointLight>(Vector{0, 1.6f, 1.0f}, Color{1, 1, 1}, 1.75f));

  scene.addObject(std::make_shared<Rectangle>(Vector(-2, -1, -1), Vector(1, 0, 0), Vector(0, 0, 1), Vector(0, 1, 0), 3, 3, materialWallRed));
  scene.addObject(std::make_shared<Rectangle>(Vector(2, 2, 2), Vector(-1, 0, 0), Vector(0, 0, -1), Vector(0, -1, 0), 3, 3, materialWallGreen));
  scene.addObject(std::make_shared<Rectangle>(Vector(-2, -1, -1), Vector(0, 1, 0), Vector(1, 0, 0), Vector(0, 0, 1), 4, 3, materialGround));
  scene.addObject(std::make_shared<Rectangle>(Vector(-2, 2, -1), Vector(0, -1, 0), Vector(1, 0, 0), Vector(0, 0, 1), 4, 3, materialGround));
  scene.addObject(std::make_shared<Rectangle>(Vector(-2, -1, 2), Vector(0, 0, -1), Vector(1, 0, 0), Vector(0, 1, 0), 4, 3, materialGround));
  scene.addObject(std::make_shared<Rectangle>(Vector(-2, -1, -1), Vector(0, 0, 1), Vector(1, 0, 0), Vector(0, 1, 0), 4, 3, materialGround));
  scene.addObject(std::make_shared<Sphere>(Vector(-0.8f, -0.5f, 0.8f), 0.5f, materialGround));
  scene.addObject(std::make_shared<Sphere>(Vector(0.6f, -0.5f, 0.3f), 0.5f, materialMirror));

  const auto then = std::chrono::steady_clock::now();

  const Image render = renderer.render(std::move(camera), scene);

  const auto now = std::chrono::steady_clock::now();
  const std::chrono::duration<double> elapsed = now - then;
  float sec = elapsed.count();
  int min = sec / 60;
  sec -= min * 60;
  int hours = min / 60;
  min -= hours * 60;
  std::cout << "\aFinished rendering in ";
  if(hours > 0) std::cout << hours << "h ";
  if(min > 0) std::cout << min << "m ";
  std::cout << sec << "s\n";

  render.save("render.ppm");

  return 0;
}