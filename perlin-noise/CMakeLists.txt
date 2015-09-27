cmake_minimum_required(VERSION 2.8)

project(perlin-noise)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

set(SOURCE_FILES src/main.cpp)
add_executable(perlin-noise ${SOURCE_FILES})
target_link_libraries(perlin-noise ${SDL2_LIBRARY})
