#include "bakr/polygon_with_holes.h"

#include <cassert>
#include <algorithm>

#include "bakr/predicates.h"
#include "bakr/predicates_vertex.h"


namespace bakr {

std::vector<IntPoint>::const_iterator xmax_vertex(const std::vector<IntPoint>& polygon) {
  return std::max_element(polygon.begin(), polygon.end(), 
      [](const IntPoint& p0, const IntPoint& p1) -> bool {return p0.X < p1.X;});
}

std::vector<IntPoint*>::const_iterator xmax_vertex(const std::vector<IntPoint*>& polygon) {
  return std::max_element(polygon.begin(), polygon.end(), 
      [](const IntPoint* p0, const IntPoint* p1) -> bool {return p0->X < p1->X;});
}

std::vector<const IntPoint*> connect_polygon_with_hole(const std::vector<const IntPoint*>& boundary, const std::vector<IntPoint>& hole) {
  size_t n = boundary.size() + hole.size() + 2;
  std::vector<const IntPoint*> result;
  result.reserve(n);

  std::vector<IntPoint>::const_iterator v_hole = xmax_vertex(hole);
  std::vector<IntPoint>::const_iterator v_hole_next = v_hole+1==hole.end() ? hole.begin() : v_hole+1;
  std::vector<IntPoint>::const_iterator v_hole_previous = v_hole==hole.begin() ? hole.end()-1 : v_hole-1;
  std::vector<const IntPoint*>::const_iterator v_boundary = boundary.begin();

  for (; v_boundary!=boundary.end(); ++v_boundary) {
    if ((*v_boundary)->X > (*v_hole).X
        && predicate::is_in_cone(*v_hole_previous, *v_hole, *v_hole_next, **v_boundary)
        && predicate::is_visible(*v_boundary, &(*v_hole), boundary)) {
      std::vector<const IntPoint*>::const_iterator v_boundary_next = v_boundary+1==boundary.end() ? boundary.begin() : v_boundary+1;
      std::vector<const IntPoint*>::const_iterator v_boundary_previous = v_boundary==boundary.begin() ? boundary.end()-1 : v_boundary-1;
      if (predicate::is_in_cone(**v_boundary_previous, **v_boundary, **v_boundary_next, *v_hole)) {
        break;
      }
    }
  }
  assert(v_boundary!=boundary.end());

  result.insert(result.end(), v_boundary, boundary.end());
  result.insert(result.end(), boundary.begin(), v_boundary+1);

  std::transform(v_hole, hole.end(), std::back_inserter(result), [](const IntPoint& p) {return &p;});
  std::transform(hole.begin(), v_hole+1, std::back_inserter(result), [](const IntPoint& p) {return &p;});
  return result;
}

using Polygon = std::vector<IntPoint>;

std::vector<const IntPoint*> connect_polygon_with_holes(const Polygon& polygon, const std::vector<Polygon>& holes) {
  std::vector<std::pair<IntType, const Polygon*>> holes_sorted;
  holes_sorted.reserve(holes.size());
  std::transform(holes.begin(), holes.end(), std::back_inserter(holes_sorted), [](const Polygon& polygon) -> std::pair<IntType, const Polygon*> {return {xmax_vertex(polygon)->X, &polygon};});
  std::sort(holes_sorted.begin(), holes_sorted.end());
  std::reverse(holes_sorted.begin(), holes_sorted.end());


  std::vector<const IntPoint*> current_polygon;
  current_polygon.reserve(polygon.size());
  std::transform(polygon.begin(), polygon.end(), std::back_inserter(current_polygon), [](const IntPoint& p) {return &p;});
  for (auto& xmax_hole: holes_sorted) {
    const std::vector<IntPoint>& hole = *std::get<1>(xmax_hole);
    current_polygon = connect_polygon_with_hole(current_polygon, hole);
  }
  return current_polygon;
}

} // namespace bakr
