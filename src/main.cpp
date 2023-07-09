#include <chrono>
#include <fstream>
#include <memory>

#include "AreaLight.hpp"
#include "CheckerboardTexture.hpp"
#include "Cylinder.hpp"
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
  parameters.mcSamples = 32;
  parameters.saveIntermediate = true;
  parameters.seed = 42;

  auto integrator = std::make_shared<PathTracer>();
  Renderer renderer{parameters, integrator};

  std::cout << parameters << "\n";

  const auto sunDirection = Vector3f{-1.0f, 2.0f, 1.0f}.normalized();
  const float observerAltitude = 24 * 5.0f;
  auto skyParameters = SingleScatteringSky::getDefaultParameters();
  skyParameters.scatteringSamples = 64;
  skyParameters.opticalDensitySamples = 32;

  auto environment =
      std::make_unique<SingleScatteringSky>(skyParameters, sunDirection, observerAltitude);

  auto camera =
      std::make_unique<PinholeCamera>(90.0f, Vector3f{0, observerAltitude, -0.7},
                                      Vector3f{0, -0.1, 1}.normalized(), Vector3f{0, 1, 0});

  Scene scene{std::move(environment)};

  auto colorWhite = std::make_shared<SolidTexture>(Color{1.0f, 1.0f, 1.0f});
  auto colorRed = std::make_shared<SolidTexture>(Color{1.0f, 0.0f, 0.0f});

  auto materialWhite = std::make_shared<DiffuseMaterial>(colorWhite, 0.8);
  auto materialRed = std::make_shared<DiffuseMaterial>(colorRed, 0.8);
  auto materialMirror = std::make_shared<MirrorMaterial>(colorWhite);

  scene.addObject(std::make_shared<Rectangle>(Vector3f(-50000, 0, -50000), Vector3f(0, 1, 0),
                                              Vector3f(1, 0, 0), Vector3f(0, 0, 1), 100000, 100000,
                                              materialWhite));
  // scene.addObject(std::make_shared<Sphere>(Vector3f(1.0f, 0.5f, 0.9f), 0.5f, materialMirror));

  for (int z = 0; z < 20; ++z) {
    Transformation transformation;
    transformation.setTranslation(Vector3f(600 - z * 30, 500.0f, 500.0f + z * 1000.0f));
    scene.addObject(std::make_shared<Cylinder>(transformation, 20.0f, 1000.0f, materialWhite));
  }

  // for (int x = 0; x < 50; ++x) {
  //   for (int z = 0; z < 50; ++z) {
  //     Transformation transformation;
  //     transformation.setTranslation(Vector3f((x - 25) * 100.0f, 25.0f, 200.0f + z * 200.0f));
  //     scene.addObject(std::make_shared<Cylinder>(transformation, 30.0f, 50.0f, materialWhite));
  //   }
  // }

  // Transformation meshTransformation;
  // meshTransformation.setScale(Vector3f(1.3f));
  // meshTransformation.setTranslation(Vector3f(-0.8f, -1.0f, 0.8f));
  // meshTransformation.setRotation(Vector3f(0.0f, -PI / 4.0, 0.0f));
  // auto mesh = ObjLoader::load("./meshes/lucy-low.obj", meshTransformation, materialWhite);
  // scene.addObject(mesh);

  scene.addLight(
      std::make_shared<DirectionalLight>(Vector3f(0, -1, -1).normalized(), Color(1.0f), 2.0f));

  // scene.addLight(std::make_shared<AreaLight>(
  //     std::make_shared<Rectangle>(Vector3f(-0.3f, 0.0f, 1.0f), Vector3f(-1, 0, -1).normalized(),
  //                                 Vector3f(1, 0, -1).normalized(), Vector3f(1, 1,
  //                                 0).normalized(), 0.8f, 0.5f, materialWhite),
  //     Color(1, 15, 1)));

  Stopwatch watch = Stopwatch::startNew();
  const Image render = renderer.render(std::move(camera), scene);
  watch.stop();

  std::cout << "Finished rendering in " << watch.getElapsedTime();

  render.save("render.hdr");

  return 0;
}