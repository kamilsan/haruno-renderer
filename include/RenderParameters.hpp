#ifndef RENDER_PARAMETERS_HPP
#define RENDER_PARAMETERS_HPP

#include <iostream>

struct RenderParameters {
  unsigned int width;
  unsigned int height;
  unsigned int numTiles;
  unsigned int threads;
  unsigned int mcSamples;

  friend std::ostream& operator<<(std::ostream& os, const RenderParameters& params) {
    os << "Image resolution: " << params.width << "x" << params.height << "\n";
    os << "Samples per pixel: " << params.mcSamples << "\n";
    os << "Number of tiles: " << params.numTiles << "\n";
    os << "CPU Threads used: " << params.threads << "\n";
    
    return os;
  }
};

#endif