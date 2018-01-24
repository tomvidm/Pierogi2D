project(p2d-core)

add_subdirectory(input)
add_subdirectory(math)

add_library(p2d-core
    p2d_window.cpp
    p2d_clock.cpp
    )

set_target_properties(p2d-core
    PROPERTIES 
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    )

target_link_libraries(p2d-core PUBLIC
    ${SDL2_LIBRARIES}
    )

target_include_directories(p2d-core PUBLIC
    ${SDL2_INCLUDE_DIR}
    
    )