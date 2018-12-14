cmake_minimum_required(VERSION 3.0.0)

project(bakr-triangulation VERSION 0.1.0)

set (CMAKE_CXX_STANDARD 11)
# set (CMAKE_CXX_FLAGS "-Wall -Wextra -Wundef -Wcast-align -Wwrite-strings -Wmissing-declarations -Wredundant-decls -Woverloaded-virtual -pthread")
set (CMAKE_CXX_FLAGS "-Wall -Wextra -Wundef -Wcast-align -Wwrite-strings -Wredundant-decls -Woverloaded-virtual -pthread")

include(CTest)
enable_testing()

include_directories(
    include
    .
    /home/sebastian/catkin_ws/src/wigeon/include
)

add_library(bakr-triangulation
    src/triangulation.cpp)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# Testing
option(ENABLE_EXAMPLES "Enable examples" ON)
if (${ENABLE_TESTS})
    add_subdirectory(examples)
endif()

# Testing
option(ENABLE_TESTS "Enable tests" ON)
if (${ENABLE_TESTS})
    enable_testing()
    add_subdirectory(tests)
endif()

# Benchmarks
option(ENABLE_BENCHMARKS "Enable benchmarks" ON)
if (${ENABLE_TESTS})
    add_subdirectory(perf)
endif()
