add_subdirectory(pierogi)

add_executable(sdl2eng WIN32 main.cpp)

target_link_libraries(sdl2eng PUBLIC
    pierogi
    ${SDL2_LIBRARIES}
    )

target_include_directories(sdl2eng PUBLIC
    ${SRC_DIR}/pierogi
    ${SDL2_INCLUDE_DIR}
    )