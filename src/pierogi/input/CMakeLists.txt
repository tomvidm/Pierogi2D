project(p2d-input)

#add_subdirectory(math)

add_library(p2d-input
    p2d_event.cpp
    p2d_eventhandler.cpp
    p2d_mouseeventhandler.cpp
    p2d_mousestate.cpp
    )

set_target_properties(p2d-input
    PROPERTIES 
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    )

target_link_libraries(p2d-input PUBLIC
    ${SDL2_LIBRARIES}
    )

target_include_directories(p2d-input PUBLIC
    ${SDL2_INCLUDE_DIR}
    )