#include "ObjLoader.hpp"

#include <fstream>
#include <sstream>
#include <unordered_map>

#include "Vector2.hpp"

std::shared_ptr<TriangleMesh> ObjLoader::load(const std::string& filename,
                                              const Transformation& transformation,
                                              std::shared_ptr<Material> material) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    throw std::runtime_error("Could not load mesh from file " + filename);
  }

  // Those arrays may have different size
  std::vector<Vector3f> verticesUnique;
  std::vector<Vector2f> uvsUnique;
  std::vector<Vector3f> normalsUnique;

  std::unordered_map<std::string, unsigned int> vertexDataIndices;

  // Those must have the same size
  std::vector<Vector3f> vertices;
  std::vector<Vector2f> uvs;
  std::vector<Vector3f> normals;
  std::vector<unsigned int> indices;

  std::string line;
  while (std::getline(file, line)) {
    std::stringstream lineStream(line);

    std::string marker;
    lineStream >> marker;

    if (marker == "v") {
      float x, y, z;
      lineStream >> x >> y >> z;
      verticesUnique.emplace_back(Vector3f(x, y, z));
    } else if (marker == "vt") {
      float u, v;
      lineStream >> u >> v;
      uvsUnique.emplace_back(Vector2f(u, v));
    } else if (marker == "vn") {
      float x, y, z;
      lineStream >> x >> y >> z;
      normalsUnique.emplace_back(Vector3f(x, y, z).normalized());
    } else if (marker == "f") {
      std::string vertexIndices;
      for (size_t i = 0; i < 3; ++i) {
        lineStream >> vertexIndices;

        const auto it = vertexDataIndices.find(vertexIndices);
        if (it != vertexDataIndices.end()) {
          indices.emplace_back(it->second);
        } else {
          const auto firstSlashPos = vertexIndices.find_first_of('/', 0);
          const auto secondSlashPos = vertexIndices.find_first_of('/', firstSlashPos + 1);

          const auto positionIndex = std::stoul(vertexIndices.substr(0, firstSlashPos));

          unsigned long uvIndex = 1ul;
          const auto uvIndexStrLen = secondSlashPos - firstSlashPos - 1;
          const auto uvIndexStr = vertexIndices.substr(firstSlashPos + 1, uvIndexStrLen);
          if (!uvIndexStr.empty()) {
            uvIndex = std::stoul(uvIndexStr);
          }

          const auto normalIndex = std::stoul(vertexIndices.substr(secondSlashPos + 1));

          // Indices in OBJ file format start from 1, not 0
          vertices.emplace_back(verticesUnique[positionIndex - 1]);
          uvs.emplace_back(uvsUnique[uvIndex - 1]);
          normals.emplace_back(normalsUnique[normalIndex - 1]);

          const auto newIndex = vertexDataIndices.size();
          indices.emplace_back(newIndex);
          vertexDataIndices.insert({vertexIndices, newIndex});
        }
      }
    }
  }

  file.close();

  return std::make_shared<TriangleMesh>(vertices, normals, uvs, indices, transformation, material);
}