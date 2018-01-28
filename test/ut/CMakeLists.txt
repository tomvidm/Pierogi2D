project(p2d-unittests )

set(UT_SOURCES
    test_p2d_circularbuffer.cpp
    test_p2d_vector.cpp
    test_p2d_rect.cpp
    test_p2d_quadtree.cpp
    )

add_executable(p2d-unittests
    ${gtest_SOURCE_DIR}/src/gtest_main.cc
    ${UT_SOURCES}
    )

set_target_properties(p2d-unittests
    PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin-ut
    )

target_link_libraries(p2d-unittests
    gtest
    p2d-core
    p2d-graphics
    p2d-math
    p2d-utility
    )

target_include_directories(p2d-unittests PUBLIC 
    ${GTEST_INCLUDE_DIR}
    ${GTEST_DIR}
    ${SRC_DIR}/pierogi/
    ${SRC_DIR}/pierogi/graphics
    ${SRC_DIR}/pierogi/math
    ${SRC_DIR}/pierogi/utility)