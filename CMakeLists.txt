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

add_executable(example-triangulation
    examples/triangulation.cpp
)

add_executable(perf-triangulation
    perf/triangulation.cpp
)

add_executable(perf-isincone
    perf/is_in_cone.cpp
)

target_link_libraries(perf-triangulation
    benchmark
)

target_link_libraries(perf-isincone
    benchmark
)

target_link_libraries(example-triangulation
    wigeon
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
