#include "ObjLoader.hpp"

#include <fstream>
#include <sstream>

std::shared_ptr<TriangleMesh> ObjLoader::load(const std::string& filename,
                                              std::shared_ptr<Material> material) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    throw std::runtime_error("Could not load mesh from file " + filename);
  }

  std::vector<Vector> vertices;
  std::vector<unsigned int> indices;

  std::string line;
  while (std::getline(file, line)) {
    std::stringstream lineStream(line);

    std::string marker;
    lineStream >> marker;

    if (marker == "v") {
      float x, y, z;
      lineStream >> x >> y >> z;
      vertices.emplace_back(Vector(x, y, z));
    } else if (marker == "f") {
      std::string vertexIndices;
      for (size_t i = 0; i < 3; ++i) {
        lineStream >> vertexIndices;
        const auto slashIndex = vertexIndices.find_first_of('/', 0);
        const auto index = std::stoul(vertexIndices.substr(0, slashIndex));
        indices.emplace_back(index - 1);
      }
    }
  }

  file.close();

  std::cout << "Vertices: " << vertices.size() << "\n";
  std::cout << "Triangles: " << indices.size() / 3 << "\n";
  std::cout << "Indices: " << indices.size() << "\n";

  return std::make_shared<TriangleMesh>(vertices, indices, material);
}