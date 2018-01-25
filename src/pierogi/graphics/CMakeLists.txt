project(p2d-graphics)

add_library(p2d-graphics
    p2d_graphics.cpp
    )

set_target_properties(p2d-graphics
    PROPERTIES 
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    )

target_link_libraries(p2d-graphics PUBLIC
    ${SDL2_LIBRARIES}
    p2d-debug
    p2d-math
    )

target_include_directories(p2d-graphics PUBLIC 
    ${SDL2_INCLUDE_DIR}
    ${SRC_DIR}/pierogi/debug
    ${SRC_DIR}/pierogi/math
    )

