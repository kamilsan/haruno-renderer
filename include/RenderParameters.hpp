#ifndef RENDER_PARAMETERS_HPP
#define RENDER_PARAMETERS_HPP

#include <iostream>
#include <thread>

struct RenderParameters {
  unsigned int width = 1920;
  unsigned int height = 1080;
  unsigned int numTiles = 200;
  unsigned int threads = std::thread::hardware_concurrency();
  unsigned int mcSamples = 256;
  unsigned int saveFrequency = 10;
  bool saveIntermediate = false;

  friend std::ostream& operator<<(std::ostream& os, const RenderParameters& params) {
    os << "Image resolution: " << params.width << "x" << params.height << "\n";
    os << "Samples per pixel: " << params.mcSamples << "\n";
    os << "Number of tiles: " << params.numTiles << "\n";
    os << "CPU Threads used: " << params.threads << "\n";
    os << "Save intermediate results: " << std::boolalpha << params.saveIntermediate << "\n";
    os << "Intermediate results save frequency: " << params.saveFrequency << "\n";
    
    return os;
  }
};

#endif