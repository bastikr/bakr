add_executable(example-triangulation
    triangulation.cpp
)

target_link_libraries(example-triangulation
    bakr-triangulation
    wigeon
)
