project(p2d)

add_subdirectory(pierogi)

add_executable(p2d main.cpp)

set (CMAKE_CXX_STANDARD 11)

set_target_properties(p2d 
    PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    )

target_link_libraries(p2d PUBLIC
    p2d-core
    p2d-input
    p2d-utility
    ${SDL2_LIBRARIES}
    #${GLEW_LIBRARIES}
    )

target_include_directories(p2d PUBLIC
    ${SRC_DIR}/pierogi
    ${SRC_DIR}/pierogi/math
    ${SRC_DIR}/pierogi/input
    ${SRC_DIR}/pierogi/utility
    ${SDL2_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIR}
    )