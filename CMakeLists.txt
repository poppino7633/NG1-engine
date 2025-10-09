cmake_minimum_required(VERSION 3.15...4.0)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra")
project(
  NG1
  VERSION 1.0
  DESCRIPTION "OpenGL graphics engine"
  LANGUAGES C CXX
)

add_subdirectory(extern/glfw)
add_subdirectory(extern/glm)

add_subdirectory(src)
add_subdirectory(apps)


