#include "Renderer.hpp"
#include "PinholeCamera.hpp"
#include "Sphere.hpp"
#include "Plane.hpp"
#include "Rectangle.hpp"
#include "Scene.hpp"
#include "SolidMaterial.hpp"
#include "MirrorMaterial.hpp"
#include "SimpleEnvironment.hpp"
#include "DirectionalLight.hpp"
#include "PointLight.hpp"

#include <memory>

int main()
{
  Renderer renderer{1920, 1080, 256, 3};
  
  auto camera = std::make_unique<PinholeCamera>(90.0f, Vector{0, 0, -1}, Vector{0, 0, 1}, Vector{0, 1, 0});
  
  const Color zenith{0.176f, 0.557f, 0.988f};
  const Color horizon{0.71f, 0.259f, 0.149f};
  const Color ground{0.467f, 0.384f, 0.325f};
  auto environment = std::make_unique<SimpleEnvironment>(zenith, horizon, ground); 

  Scene scene{std::move(environment)};

  auto materialWall1 = std::make_shared<SolidMaterial>(Color{0.9f, 0.1f, 0.05f}, 0.6f);
  auto materialWall2 = std::make_shared<SolidMaterial>(Color{0.1f, 0.9f, 0.05f}, 0.6f);
  auto materialGround = std::make_shared<SolidMaterial>(Color{1.0f, 1.0f, 1.0f}, 0.6f);
  auto materialMirror = std::make_shared<MirrorMaterial>(Color{1.0f, 1.0f, 1.0f});

  scene.addLight(std::make_shared<PointLight>(Vector{0, 1.6f, 1.0f}, Color{1, 1, 1}, 1.75f));

  scene.addObject(std::make_shared<Rectangle>(Vector(-2, -1, -1), Vector(1, 0, 0), Vector(0, 0, 1), Vector(0, 1, 0), 3, 3, materialWall1));
  scene.addObject(std::make_shared<Rectangle>(Vector(2, 2, 2), Vector(-1, 0, 0), Vector(0, 0, -1), Vector(0, -1, 0), 3, 3, materialWall2));
  scene.addObject(std::make_shared<Rectangle>(Vector(-2, -1, -1), Vector(0, 1, 0), Vector(1, 0, 0), Vector(0, 0, 1), 4, 3, materialGround));
  scene.addObject(std::make_shared<Rectangle>(Vector(-2, 2, -1), Vector(0, -1, 0), Vector(1, 0, 0), Vector(0, 0, 1), 4, 3, materialGround));
  scene.addObject(std::make_shared<Rectangle>(Vector(-2, -1, 2), Vector(0, 0, -1), Vector(1, 0, 0), Vector(0, 1, 0), 4, 3, materialGround));
  scene.addObject(std::make_shared<Rectangle>(Vector(-2, -1, -1), Vector(0, 0, 1), Vector(1, 0, 0), Vector(0, 1, 0), 4, 3, materialGround));
  scene.addObject(std::make_shared<Sphere>(Vector(-0.8f, -0.5f, 0.8f), 0.5f, materialGround));
  scene.addObject(std::make_shared<Sphere>(Vector(0.6f, -0.5f, 0.3f), 0.5f, materialMirror));

  const Image render = renderer.render(std::move(camera), scene);

  render.save("render.ppm");

  return 0;
}