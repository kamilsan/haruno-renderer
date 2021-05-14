#include "Renderer.hpp"
#include "PinholeCamera.hpp"

int main()
{
  Renderer renderer;
  auto camera = std::make_unique<PinholeCamera>();
  const Image render = renderer.render(std::move(camera), 1920, 1080);

  render.save("render.ppm");

  return 0;
}