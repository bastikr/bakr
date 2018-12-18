#include "bakr/transformation.h"

namespace bakr {

std::vector<IntPoint> shift(IntType shift_x, IntType shift_y, const std::vector<IntPoint>& polygon) {
  std::vector<IntPoint> result;
  result.reserve(polygon.size());
  for (const IntPoint& p: polygon) {
    result.push_back({shift_x + p.X, shift_y + p.Y});
  }
  return result;
}

std::vector<IntPoint> scale(IntType scale_x, IntType scale_y, const std::vector<IntPoint>& polygon) {
  std::vector<IntPoint> result;
  result.reserve(polygon.size());
  for (const IntPoint& p: polygon) {
    result.push_back({scale_x*p.X, scale_y*p.Y});
  }
  return result;
}

std::vector<IntPoint> rotate90(const std::vector<IntPoint>& polygon) {
  std::vector<IntPoint> result;
  result.reserve(polygon.size());
  for (const IntPoint& p: polygon) {
    result.push_back({-p.Y, p.X});
  }
  return result;
}

std::vector<IntPoint> rotate180(const std::vector<IntPoint>& polygon) {
  std::vector<IntPoint> result;
  result.reserve(polygon.size());
  for (const IntPoint& p: polygon) {
    result.push_back({-p.X, -p.Y});
  }
  return result;
}

std::vector<IntPoint> rotate270(const std::vector<IntPoint>& polygon) {
  std::vector<IntPoint> result;
  result.reserve(polygon.size());
  for (const IntPoint& p: polygon) {
    result.push_back({p.Y, -p.X});
  }
  return result;
}

} // namespace bakr
