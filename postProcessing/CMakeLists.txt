cmake_minimum_required(VERSION 3.20.5)

project(raytracer_primitive)
# find_package(Curses REQUIRED)             //find package

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib/)
set(CMAKE_SHARED_LIBRARY_PREFIX "")

set(
DROP_SOURCES
    drop/Drop.cpp
)

set(
AMBIENT_SOURCES
    ambient/Ambient.cpp
)

add_library(raytracer_drop SHARED ${DROP_SOURCES})
target_include_directories(raytracer_drop PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../inc)
target_include_directories(raytracer_drop PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(raytracer_drop PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../primitive)
target_include_directories(raytracer_drop PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../lights)

add_library(raytracer_ambientp SHARED ${AMBIENT_SOURCES})
target_include_directories(raytracer_ambientp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../inc)
target_include_directories(raytracer_ambientp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(raytracer_ambientp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../primitive)
target_include_directories(raytracer_ambientp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../lights)
