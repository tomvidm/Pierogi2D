project(p2d-core)

add_subdirectory(debug)
add_subdirectory(graphics)
add_subdirectory(math)
add_subdirectory(input)

add_library(p2d-core
    p2d_window.cpp
    p2d_clock.cpp
    p2d_instance.cpp
    )

set_target_properties(p2d-core
    PROPERTIES 
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    )

target_link_libraries(p2d-core PUBLIC
    ${OPENGL_LIBRARIES}
    ${SDL2_LIBRARIES}
    ${GLEW_LIBRARIES}
    p2d-debug
    p2d-input
    p2d-math
    )

target_include_directories(p2d-core PUBLIC
    ${OPENGL_INCLUDE_DIR}
    ${SDL2_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIR}
    ${SRC_DIR}/pierogi
    ${SRC_DIR}/pierogi/debug
    ${SRC_DIR}/pierogi/input
    ${SRC_DIR}/pierogi/math
    ${SRC_DIR}/pierogi/utility
    )