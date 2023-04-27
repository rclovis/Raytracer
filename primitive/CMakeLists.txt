cmake_minimum_required(VERSION 3.20.5)

project(raytracer_primitive)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib/)
set(CMAKE_SHARED_LIBRARY_PREFIX "")

set(
SPHERE_SOURCES
    sphere/Sphere.cpp
)

add_library(raytracer_sphere SHARED ${SPHERE_SOURCES})
target_include_directories(raytracer_sphere PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../inc)
target_include_directories(raytracer_sphere PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
