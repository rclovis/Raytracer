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

set(
PLANE_SOURCES
    plane/Plane.cpp
)

set(
SQUARE_SOURCES
    square/Square.cpp
)

set(
CYLINDRE_SOURCES
    cylindre/Cylindre.cpp
TRIANGLE_SOURCES
    triangle/Triangle.cpp
)

set(
OBJ_SOURCES
    obj/Obj.cpp
)

add_library(raytracer_sphere SHARED ${SPHERE_SOURCES})
target_include_directories(raytracer_sphere PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../inc)
target_include_directories(raytracer_sphere PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(raytracer_plane SHARED ${PLANE_SOURCES})
target_include_directories(raytracer_plane PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../inc)
target_include_directories(raytracer_plane PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(raytracer_square SHARED ${SQUARE_SOURCES})
target_include_directories(raytracer_square PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../inc)
target_include_directories(raytracer_square PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

<<<<<<< HEAD
add_library(raytracer_cylindre SHARED ${CYLINDRE_SOURCES})
target_include_directories(raytracer_cylindre PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../inc)
target_include_directories(raytracer_cylindre PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
=======
add_library(raytracer_triangle SHARED ${TRIANGLE_SOURCES})
target_include_directories(raytracer_triangle PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../inc)
target_include_directories(raytracer_triangle PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(raytracer_obj SHARED ${OBJ_SOURCES})
target_include_directories(raytracer_obj PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../inc)
target_include_directories(raytracer_obj PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

>>>>>>> 359821935dd225378b3017360dfa8acb742d21c3

target_link_libraries(raytracer_sphere config++)
target_link_libraries(raytracer_plane config++)
target_link_libraries(raytracer_square config++)
target_link_libraries(raytracer_cylindre config++)