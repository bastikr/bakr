#pragma once

#include <vector>

#include "bakr/intpoint.h"
#include "bakr/vertex.h"
#include "bakr/partition.h"


namespace bakr {

std::vector<std::array<IntPoint, 3>> triangles(const TriangleTree& tree);

std::vector<const IntPoint*> connect_polygon_with_holes(const std::vector<IntPoint>& polygon, const std::vector<std::vector<IntPoint>>& holes);

namespace triangulation {

namespace graph {

TriangleTree ear_clipping(const std::vector<IntPoint>& polygon);
TriangleTree ear_clipping(const std::vector<const IntPoint*>& polygon);

} // namespace graph

} // namespace triangulation

} // namespace bakr
