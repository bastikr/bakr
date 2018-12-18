#pragma once

#include <vector>

#include "bakr/intpoint.h"


namespace bakr {

std::vector<IntPoint> shift(IntType shift_x, IntType shift_y, const std::vector<IntPoint>& polygon);
std::vector<IntPoint> scale(IntType scale_x, IntType scale_y, const std::vector<IntPoint>& polygon);

std::vector<IntPoint> rotate90(const std::vector<IntPoint>&);
std::vector<IntPoint> rotate180(const std::vector<IntPoint>&);
std::vector<IntPoint> rotate270(const std::vector<IntPoint>&);

} // namespace bakr
