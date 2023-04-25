cmake_minimum_required(VERSION 3.20.5)

project(raytracer_primitive)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib/)
set(CMAKE_SHARED_LIBRARY_PREFIX "")

set(
CIRCLE_SOURCES
    circle/Circle.cpp
)

add_library(raytracer_circle SHARED ${CIRCLE_SOURCES})
target_include_directories(raytracer_circle PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../inc)
target_include_directories(raytracer_circle PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
