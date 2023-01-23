#include <chrono>
#include <fstream>
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
#include "SingleScatteringSky.hpp"
#include "SolidTexture.hpp"
#include "Sphere.hpp"
#include "Stopwatch.hpp"
#include "TriangleMesh.hpp"

int main() {
  RenderParameters parameters;
  parameters.width = 1920;
  parameters.height = 1080;
  parameters.numTiles = 400;
  parameters.threads = 8;
  parameters.mcSamples = 64;
  parameters.saveIntermediate = true;
  parameters.seed = 42;

  auto integrator = std::make_shared<PathTracer>();
  Renderer renderer{parameters, integrator};

  std::cout << parameters << "\n";

  const auto sunDirection = Vector3f{-1.0f, 2.0f, 1.0f}.normalized();
  const float observerAltitude = 1.73f;

  auto environment = std::make_unique<SingleScatteringSky>(sunDirection, observerAltitude);

  auto camera = std::make_unique<SimpleCamera>(90.0f, 0.03f, 1.07f, Vector3f{0, 0.8f, -0.7},
                                               Vector3f{0, 0, 1}, Vector3f{0, 1, 0});

  Scene scene{std::move(environment)};

  auto colorWhite = std::make_shared<SolidTexture>(Color{1.0f, 1.0f, 1.0f});
  auto colorRed = std::make_shared<SolidTexture>(Color{1.0f, 0.0f, 0.0f});

  auto materialWhite = std::make_shared<DiffuseMaterial>(colorWhite, 0.8);
  auto materialRed = std::make_shared<DiffuseMaterial>(colorRed, 0.8);
  auto materialMirror = std::make_shared<MirrorMaterial>(colorWhite);

  scene.addObject(std::make_shared<Rectangle>(Vector3f(-50000, 0, -50000), Vector3f(0, 1, 0),
                                              Vector3f(1, 0, 0), Vector3f(0, 0, 1), 100000, 100000,
                                              materialWhite));
  scene.addObject(std::make_shared<Sphere>(Vector3f(1.0f, 0.5f, 0.9f), 0.5f, materialMirror));

  // Transformation meshTransformation;
  // meshTransformation.setScale(Vector3f(1.3f));
  // meshTransformation.setTranslation(Vector3f(-0.8f, -1.0f, 0.8f));
  // meshTransformation.setRotation(Vector3f(0.0f, -PI / 4.0, 0.0f));
  // auto mesh = ObjLoader::load("./meshes/lucy-low.obj", meshTransformation, materialWhite);
  // scene.addObject(mesh);

  scene.addLight(std::make_shared<DirectionalLight>(Vector3f(0, -1, 0), Color(1.0f), 2.0f));

  scene.addLight(std::make_shared<AreaLight>(
      std::make_shared<Rectangle>(Vector3f(-0.3f, 0.0f, 1.0f), Vector3f(-1, 0, -1).normalized(),
                                  Vector3f(1, 0, -1).normalized(), Vector3f(1, 1, 0).normalized(),
                                  0.8f, 0.5f, materialWhite),
      Color(1, 15, 1)));

  Stopwatch watch = Stopwatch::startNew();
  const Image render = renderer.render(std::move(camera), scene);
  watch.stop();

  std::cout << "Finished rendering in " << watch.getElapsedTime();

  render.save("render.hdr");

  return 0;
}