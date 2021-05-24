cmake_minimum_required(VERSION 2.4)
project(PathTracer)

if(COMMAND cmake_policy)
  cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CMAKE_CXX_STANDARD 17)

set(PROJECT_CODE
  include/Color.hpp
  include/Ray.hpp
  include/Camera.hpp
  include/Object.hpp
  include/Sphere.hpp
  include/Plane.hpp
  include/Rectangle.hpp
  include/Material.hpp
  include/SolidMaterial.hpp
  include/Environment.hpp
  include/Light.hpp
  include/DirectionalLight.hpp
  include/PointLight.hpp
  include/BRDF.hpp
  include/LambertBRDF.hpp
  include/RNG.hpp
  include/Image.hpp src/Image.cpp
  include/Vector.hpp src/Vector.cpp
  include/Renderer.hpp src/Renderer.cpp
  include/Scene.hpp src/Scene.cpp
  include/SimpleEnvironment.hpp src/SimpleEnvironment.cpp
  include/PinholeCamera.hpp src/PinholeCamera.cpp
  include/Math.hpp src/Math.cpp
)

add_subdirectory(googletest)
include_directories(googletest include)

add_executable(PathTracer
  ${PROJECT_CODE}
  src/main.cpp
)

add_executable(test
  ${PROJECT_CODE}
  tests/ImageTest.cpp
  tests/VectorTest.cpp
  tests/RayTest.cpp
  tests/MathTest.cpp
  tests/main.cpp)

target_link_libraries(test gtest gtest_main)
