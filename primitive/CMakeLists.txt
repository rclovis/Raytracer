cmake_minimum_required(VERSION 3.20.5)

project(raytracer_primitive)
# find_package(Curses REQUIRED)             //find package

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib/)
set(CMAKE_SHARED_LIBRARY_PREFIX "")

# set(
# NCURSES_SOURCES
#     ncurses/ncurses.cpp
#     gfx.cpp
# )

# add_library(arcade_ncurses SHARED ${NCURSES_SOURCES})
# target_include_directories(arcade_ncurses PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../inc)
# target_include_directories(arcade_ncurses PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../games)
# target_link_libraries(arcade_ncurses PRIVATE ${CURSES_LIBRARIES})


