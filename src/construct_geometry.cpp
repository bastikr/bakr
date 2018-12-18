#include "bakr/construct_geometry.h"

namespace bakr {

namespace construct {

// std::vector<IntPoint> ngon(size_t n) {
//   std::vector<IntPoint> result;

// }

std::vector<IntPoint> comb(size_t n) {
  std::vector<IntPoint> result;
  result.reserve(4*n);
  result.push_back({0, 1});
  result.push_back({0, -1});
  result.push_back({2*n - 1, -1});
  result.push_back({2*n - 1, 1});
  for (size_t x=2*(n-1); x>0; x=x-2) {
    result.push_back({x, 1});
    result.push_back({x, 0});
    result.push_back({x-1, 0});
    result.push_back({x-1, 1});
  }
  return result;
}

} // namespace construct

} // namespace bakr
