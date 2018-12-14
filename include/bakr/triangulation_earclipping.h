#pragma once

#include <array>
#include <vector>

#include <boost/graph/adjacency_list.hpp>

#include "bakr/typedefs.h"


namespace bakr {

using Triangle = std::array<const IntPoint*, 3>;
using TriangleTree = boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, Triangle>;

std::vector<std::array<IntPoint, 3>> triangles(const TriangleTree& tree);


namespace triangulation {

namespace graph {

TriangleTree ear_clipping(const std::vector<IntPoint>& polygon);

} // namespace graph

} // namespace triangulation

} // namespace bakr
