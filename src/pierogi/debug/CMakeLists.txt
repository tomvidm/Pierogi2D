project(p2d-debug)

add_library(p2d-debug
    p2d_logger.cpp
    )

set_target_properties(p2d-debug
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    )

target_link_libraries(p2d-debug PUBLIC)

target_include_directories(p2d-debug PUBLIC)