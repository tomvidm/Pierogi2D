project(p2d-utility)

add_library(p2d-utility
    p2d_stringutils.cpp
    )

set_target_properties(p2d-utility
    PROPERTIES 
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    )