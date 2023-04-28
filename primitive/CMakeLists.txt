cmake_minimum_required(VERSION 3.20.5)

project(raytracer_primitive)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../)
include_directories(/opt/homebrew/Cellar/libconfig/1.7.3)

# Set the directory containing the libconfig library file
link_directories(/opt/homebrew/Cellar/libconfig/1.7.3/lib)

# Find the libconfig library file
set(CMAKE_PREFIX_PATH /opt/homebrew/Cellar/libconfig/1.7.3)

find_library(LIBCONFIGPP libconfig++.dylib PATHS /opt/homebrew/Cellar/libconfig/1.7.3/lib)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib/)
set(CMAKE_SHARED_LIBRARY_PREFIX "")

set(
SPHERE_SOURCES
    sphere/Sphere.cpp
)

add_library(raytracer_sphere SHARED ${SPHERE_SOURCES})
target_include_directories(raytracer_sphere PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../inc)
target_include_directories(raytracer_sphere PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(raytracer_sphere config++)