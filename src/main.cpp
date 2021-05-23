#include "Renderer.hpp"
#include "PinholeCamera.hpp"
#include "Sphere.hpp"
#include "Plane.hpp"
#include "Scene.hpp"
#include "SolidMaterial.hpp"
#include "MirrorMaterial.hpp"
#include "SimpleEnvironment.hpp"
#include "DirectionalLight.hpp"
#include "PointLight.hpp"

#include <memory>

int main()
{
  Renderer renderer{1920, 1080, 128, 3};
  
  auto camera = std::make_unique<PinholeCamera>(90.0f, Vector{0, 0, -1}, Vector{0, 0, 1}, Vector{0, 1, 0});
  
  const Color zenith{0.176f, 0.557f, 0.988f};
  const Color horizon{0.71f, 0.259f, 0.149f};
  const Color ground{0.467f, 0.384f, 0.325f};
  auto environment = std::make_unique<SimpleEnvironment>(zenith, horizon, ground); 

  Scene scene{std::move(environment)};

  auto materialSphere1 = std::make_shared<SolidMaterial>(Color{0.9f, 0.1f, 0.05f}, 0.6f);
  auto materialSphere2 = std::make_shared<SolidMaterial>(Color{0.1f, 0.9f, 0.05f}, 0.6f);
  auto materialGround = std::make_shared<SolidMaterial>(Color{1.0f, 1.0f, 1.0f}, 0.6f);
  auto materialMirror = std::make_shared<MirrorMaterial>(Color{1.0f, 1.0f, 1.0f});

  //scene.addLight(std::make_shared<DirectionalLight>(Vector{0, -1, 1}, Color{1, 1, 1}, 0.2f));
  //scene.addLight(std::make_shared<DirectionalLight>(Vector{1, -1, 1}, Color{1, 0, 0}, 0.2f));
  //scene.addLight(std::make_shared<DirectionalLight>(Vector{-1, -1, 1}, Color{0, 0, 1}, 0.2f));
  //scene.addLight(std::make_shared<PointLight>(Vector{0, 2, 1}, Color{1, 1, 1}, 0.3f));

  scene.addObject(std::make_shared<Sphere>(Vector{0, 0, 1}, 0.5f, materialSphere1));
  scene.addObject(std::make_shared<Sphere>(Vector{1, 0, 2}, 0.5f, materialMirror));
  scene.addObject(std::make_shared<Plane>(Vector{0, -0.5, 2}, Vector{0, 1, 0}, materialGround));

  const Image render = renderer.render(std::move(camera), scene);

  render.save("render.ppm");

  return 0;
}