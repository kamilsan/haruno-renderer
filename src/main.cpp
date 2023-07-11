#include <memory>

#include "AreaLight.hpp"
#include "CheckerboardTexture.hpp"
#include "DebugIntegrator.hpp"
#include "DiffuseMaterial.hpp"
#include "DirectLighting.hpp"
#include "DirectionalLight.hpp"
#include "ImageTexture.hpp"
#include "MirrorMaterial.hpp"
#include "ObjLoader.hpp"
#include "PathTracer.hpp"
#include "PinholeCamera.hpp"
#include "PointLight.hpp"
#include "Rectangle.hpp"
#include "Renderer.hpp"
#include "Scene.hpp"
#include "SimpleCamera.hpp"
#include "SimpleEnvironment.hpp"
#include "SolidTexture.hpp"
#include "Sphere.hpp"
#include "Stopwatch.hpp"
#include "TriangleMesh.hpp"

int main() {
  RenderParameters parameters;
  parameters.width = 1920;
  parameters.height = 1080;
  parameters.numTiles = 200;
  parameters.threads = 8;
  parameters.mcSamples = 64;
  parameters.seed = 42;
  parameters.saveIntermediate = true;

  auto integrator = std::make_shared<PathTracer>();
  Renderer renderer{parameters, integrator};

  std::cout << parameters << "\n";

  auto camera = std::make_unique<SimpleCamera>(90.0f, 0.01f, 1.5f, Vector3t{0, 0.1, -1},
                                               Vector3t{0, 0, 1}, Vector3t{0, 1, 0});

  auto environment = std::make_unique<SimpleEnvironment>(Color{}, Color{}, Color{});

  Scene scene{std::move(environment)};

  auto colorWhite = std::make_shared<SolidTexture>(Color{1.0f, 1.0f, 1.0f});
  auto colorRed = std::make_shared<SolidTexture>(Color{1.0f, 0.0f, 0.0f});
  auto colorGreen = std::make_shared<SolidTexture>(Color{0.0f, 1.0f, 0.0f});

  auto floor = std::make_shared<CheckerboardTexture>(8.0f, 8.0f);
  auto uvTest = std::make_shared<ImageTexture>("textures/uv.png");

  auto materialWhite = std::make_shared<DiffuseMaterial>(colorWhite, 0.8);
  auto materialRed = std::make_shared<DiffuseMaterial>(colorRed, 0.8);
  auto materialGreen = std::make_shared<DiffuseMaterial>(colorGreen, 0.8);

  auto materialUvTest = std::make_shared<DiffuseMaterial>(uvTest, 1.0f);
  auto materialFloor = std::make_shared<DiffuseMaterial>(floor, 0.8f);
  auto materialMirror = std::make_shared<MirrorMaterial>(colorWhite);

  scene.addObject(std::make_shared<Rectangle>(Vector3t(-2, -1, -1), Vector3t(1, 0, 0),
                                              Vector3t(0, 0, 1), Vector3t(0, 1, 0), 3, 3,
                                              materialRed));
  scene.addObject(std::make_shared<Rectangle>(Vector3t(2, -1, 2), Vector3t(-1, 0, 0),
                                              Vector3t(0, 0, -1), Vector3t(0, 1, 0), 3, 3,
                                              materialGreen));
  scene.addObject(std::make_shared<Rectangle>(Vector3t(-2, -1, -1), Vector3t(0, 1, 0),
                                              Vector3t(1, 0, 0), Vector3t(0, 0, 1), 4, 3,
                                              materialFloor));
  scene.addObject(std::make_shared<Rectangle>(Vector3t(-2, 2, -1), Vector3t(0, -1, 0),
                                              Vector3t(1, 0, 0), Vector3t(0, 0, 1), 4, 3,
                                              materialWhite));
  scene.addObject(std::make_shared<Rectangle>(Vector3t(-2, -1, 2), Vector3t(0, 0, -1),
                                              Vector3t(1, 0, 0), Vector3t(0, 1, 0), 4, 3,
                                              materialUvTest));
  scene.addObject(std::make_shared<Rectangle>(Vector3t(-2, -1, -1), Vector3t(0, 0, 1),
                                              Vector3t(1, 0, 0), Vector3t(0, 1, 0), 4, 3,
                                              materialWhite));
  scene.addObject(std::make_shared<Sphere>(Vector3t(-0.8f, -0.5f, 0.8f), 0.5f, materialWhite));
  scene.addObject(std::make_shared<Sphere>(Vector3t(0.6f, -0.5f, 0.4f), 0.5f, materialMirror));

  scene.addLight(std::make_shared<AreaLight>(
      std::make_shared<Rectangle>(Vector3t(-0.6f, 1.99f, 0.9f), Vector3t(0, -1, 0),
                                  Vector3t(1, 0, 0), Vector3t(0, 0, 1), 1.2f, 0.3f, materialWhite),
      Color(20, 20, 20)));

  // Transformation meshTransformation;
  // meshTransformation.setScale(Vector3t(1.3f));
  // meshTransformation.setTranslation(Vector3t(-0.8f, -1.0f, 0.8f));
  // meshTransformation.setRotation(Vector3t(0.0f, -PI / 4.0, 0.0f));
  // auto mesh = ObjLoader::load("./meshes/lucy-low.obj", meshTransformation, materialWhite);
  // scene.addObject(mesh);

  Stopwatch watch = Stopwatch::startNew();
  const Image render = renderer.render(std::move(camera), scene);
  watch.stop();

  std::cout << "Finished rendering in " << watch.getElapsedTime();

  render.save("render.hdr");

  return 0;
}