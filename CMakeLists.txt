cmake_minimum_required(VERSION 3.0)

project(sdl2eng)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenGL REQUIRED)   
find_package(SDL2 REQUIRED)   
message(STATUS ${OPENGL_INCLUDE_DIR})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

#find_package()

# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(src)
add_subdirectory(lib/googletest/googletest)
add_subdirectory(test/ut)