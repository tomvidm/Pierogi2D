project(sdl2exe)

add_subdirectory(pierogi)

add_executable(sdl2eng main.cpp)

set_target_properties(sdl2eng 
    PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    )

target_link_libraries(sdl2eng PUBLIC
    pierogi
    ${SDL2_LIBRARIES}
    )

target_include_directories(sdl2eng PUBLIC
    ${SRC_DIR}/pierogi
    ${SDL2_INCLUDE_DIR}
    )