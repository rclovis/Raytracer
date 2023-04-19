cmake_minimum_required(VERSION 3.20.5)

project(raytracer_core)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../)

set(
CORE_SOURCES
    main.cpp
    Core.cpp
    ../camera/Camera.cpp
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

target_include_directories(raytracer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../inc)
target_include_directories(raytracer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../primitive)
target_include_directories(raytracer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../camera)
