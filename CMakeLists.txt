cmake_minimum_required(VERSION 3.20.5)

project(raytracer)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(primitive)
add_subdirectory(lights)
add_subdirectory(core)
