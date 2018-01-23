project(pierogi)

add_library(pierogi
    p2d_window.cpp
    )

target_link_libraries(pierogi PUBLIC
    ${SDL2_LIBRARIES}
    )

target_include_directories(pierogi PUBLIC
    ${SDL2_INCLUDE_DIR}
    )