project(p2d-math)

add_library(p2d-math
    p2d_math.cpp
    p2d_vector.cpp
    )

set_target_properties(p2d-math
    PROPERTIES 
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    )