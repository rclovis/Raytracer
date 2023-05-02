cmake_minimum_required(VERSION 3.20.5)

project(raytracer_primitive)
# find_package(Curses REQUIRED)             //find package

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
DIRECTIONAL_SOURCES
    directional/Directional.cpp
)

set(
AMBIENT_SOURCES
    ambient/Ambient.cpp
)

set(
POINT_SOURCES
    point/Point.cpp
)

add_library(raytracer_directional SHARED ${DIRECTIONAL_SOURCES})
target_include_directories(raytracer_directional PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../inc)
target_include_directories(raytracer_directional PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(raytracer_directional PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../primitive)
target_link_libraries(raytracer_directional config++)

add_library(raytracer_ambient SHARED ${AMBIENT_SOURCES})
target_include_directories(raytracer_ambient PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../inc)
target_include_directories(raytracer_ambient PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(raytracer_ambient PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../primitive)
target_link_libraries(raytracer_ambient config++)

add_library(raytracer_point SHARED ${POINT_SOURCES})
target_include_directories(raytracer_point PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../inc)
target_include_directories(raytracer_point PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(raytracer_point PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../primitive)
target_link_libraries(raytracer_point config++)
