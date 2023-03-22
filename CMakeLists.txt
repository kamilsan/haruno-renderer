cmake_minimum_required(VERSION 3.10)
project(Haruno)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Threads)

set(PROJECT_CODE
  include/Color.hpp
  include/Ray.hpp
  include/Camera.hpp
  include/Object.hpp
  include/Sphere.hpp
  include/Rectangle.hpp
  include/Triangle.hpp
  include/TriangleMesh.hpp
  include/Material.hpp
  include/DiffuseMaterial.hpp
  include/MirrorMaterial.hpp
  include/Environment.hpp
  include/Light.hpp
  include/DirectionalLight.hpp
  include/PointLight.hpp
  include/BRDF.hpp
  include/LambertBRDF.hpp
  include/SpecularBRDF.hpp
  include/ThreadPool.hpp
  include/BaseTexture.hpp
  include/SolidTexture.hpp
  include/ImageTexture.hpp
  include/CheckerboardTexture.hpp
  include/Stopwatch.hpp
  include/Vector2.hpp
  include/Vector3.hpp
  include/Vector4.hpp
  include/Matrix4.hpp
  include/AreaLight.hpp
  include/Cylinder.hpp
  include/Cone.hpp
  include/Paraboloid.hpp
  include/ToneMapper.hpp
  include/ExposureMapper.hpp src/ExposureMapper.cpp
  include/ReinhardMapper.hpp src/ReinhardMapper.cpp
  include/Integrator.hpp src/Integrator.cpp
  include/PathTracer.hpp src/PathTracer.cpp
  include/DirectLighting.hpp src/DirectLighting.cpp
  include/DebugIntegrator.hpp src/DebugIntegrator.cpp
  include/AmbientOcclusion.hpp src/AmbientOcclusion.cpp
  include/Transformation.hpp src/Transformation.cpp
  include/Image.hpp src/Image.cpp
  include/ImageTile.hpp src/ImageTile.cpp
  include/RNG.hpp src/RNG.cpp
  include/Renderer.hpp src/Renderer.cpp
  include/RenderTileTask.hpp src/RenderTileTask.cpp
  include/Scene.hpp src/Scene.cpp
  include/SimpleEnvironment.hpp src/SimpleEnvironment.cpp
  include/PinholeCamera.hpp src/PinholeCamera.cpp
  include/SimpleCamera.hpp src/SimpleCamera.cpp
  include/Math.hpp src/Math.cpp
  include/ObjLoader.hpp src/ObjLoader.cpp
  include/BoundingBox.hpp src/BoundingBox.cpp
)

set(TEST_SOURCES
  tests/ImageTest.cpp
  tests/Vector3Test.cpp
  tests/Vector4Test.cpp
  tests/Matrix4Test.cpp
  tests/RayTest.cpp
  tests/MathTest.cpp
)

set(ALL_SOURCES
  ${PROJECT_CODE}
  ${TEST_SOURCES}
  src/main.cpp
  tests/main.cpp
)

add_custom_target(
    clang-format
    COMMAND clang-format -i ${ALL_SOURCES}
)

add_subdirectory(googletest)
include_directories(googletest include 3rd_party)

add_library(haruno-lib
  ${PROJECT_CODE}
)

set_target_properties(haruno-lib PROPERTIES OUTPUT_NAME haruno)

add_executable(haruno
  src/main.cpp
)

target_link_libraries(haruno haruno-lib ${CMAKE_THREAD_LIBS_INIT})

add_executable(test
  ${TEST_SOURCES}
  tests/main.cpp)

target_link_libraries(test haruno-lib gtest gtest_main ${CMAKE_THREAD_LIBS_INIT})
