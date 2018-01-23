project(pierogi)

add_library(pierogi
    p2d_window.cpp
    p2d_clock.cpp
    )

set_target_properties(pierogi
    PROPERTIES 
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    )

target_link_libraries(pierogi PUBLIC
    ${SDL2_LIBRARIES}
    )

target_include_directories(pierogi PUBLIC
    ${SDL2_INCLUDE_DIR}
    )