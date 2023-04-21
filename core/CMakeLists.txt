find_package(libconfig REQUIRED)

cmake_minimum_required(VERSION 3.20.5)

project(raytracer_core)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../)
include_directories(/opt/homebrew/Cellar/libconfig/1.7.3)

# Set the directory containing the libconfig library file
link_directories(/opt/homebrew/Cellar/libconfig/1.7.3/lib)

# Find the libconfig library file
set(CMAKE_PREFIX_PATH /opt/homebrew/Cellar/libconfig/1.7.3)

find_library(LIBCONFIGPP libconfig++.dylib PATHS /opt/homebrew/Cellar/libconfig/1.7.3/lib)

set(
CORE_SOURCES
    main.cpp
    Core.cpp
    ../camera/Camera.cpp
    ../parser/Parser.cpp
    DynLib.cpp
)
set(
CORE_OPTIONS
    -Wall
    -Wextra
)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    list(APPEND CORE_OPTIONS -fno-unique-internal-linkage-names)
else()
    list(APPEND CORE_OPTIONS -fno-gnu-unique)
endif()

foreach(FLAG ${CORE_OPTIONS})
    message(${FLAG})
endforeach()


add_executable(raytracer ${CORE_SOURCES})

target_compile_options(raytracer PRIVATE ${CORE_OPTIONS})

target_include_directories(raytracer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../inc)
target_include_directories(raytracer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../primitive)
target_include_directories(raytracer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../lights)
target_include_directories(raytracer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../camera)
target_include_directories(raytracer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../parser)

target_link_libraries(raytracer config++)