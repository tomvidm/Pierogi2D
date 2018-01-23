cmake_minimum_required(VERSION 3.0)

project(sdl2eng)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(SDL2_DIR "${CMAKE_SOURCE_DIR}/lib/SDL2-2.0.7")

set(SDL2_LIBRARIES
    "${SDL2_DIR}/lib/x86/SDL2.lib"
    "${SDL2_DIR}/lib/x86/SDL2main.lib"
    )

set(SDL2_INCLUDE_DIR
    "${SDL2_DIR}/include"
    )

add_subdirectory(src)