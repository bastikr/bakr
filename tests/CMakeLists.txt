find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

file(GLOB sources *.cpp)
add_executable(unittests ${sources})

target_link_libraries (unittests
    bakr-triangulation
    ${GTEST_BOTH_LIBRARIES}
)

add_test(unit ${PROJECT_BINARY_DIR}/tests/unittests)
