#pragma once

#include <vector>

#include "bakr/intpoint.h"


namespace bakr {

std::vector<const IntPoint*> connect_polygon_with_holes(const std::vector<IntPoint>& polygon, const std::vector<std::vector<IntPoint>>& holes);

} // namespace bakr
