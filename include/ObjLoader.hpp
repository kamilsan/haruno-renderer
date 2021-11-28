#ifndef OBJ_LOADER_HPP
#define OBJ_LOADER_HPP

#include <string>

#include "Transformation.hpp"
#include "TriangleMesh.hpp"

class ObjLoader {
 public:
  ObjLoader() = delete;

  static std::shared_ptr<TriangleMesh> load(const std::string& filename,
                                            const Transformation& transformation,
                                            std::shared_ptr<Material> material);

 private:
};

#endif  // OBJ_LOADER_HPP