add_executable(example-polygon-construction-comb
    polygon_construction_comb.cpp
)

add_executable(example-triangulation
    triangulation.cpp
)

add_executable(example-connect-polygon-with-holes
    connect_polygon_with_holes.cpp
)

target_link_libraries(example-polygon-construction-comb
    bakr-triangulation
    wigeon
)

target_link_libraries(example-triangulation
    bakr-triangulation
    wigeon
)

target_link_libraries(example-connect-polygon-with-holes
    bakr-triangulation
    wigeon
)
