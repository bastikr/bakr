#include "bakr/triangulation_earclipping.h"

#include <unordered_map>

#include "bakr/vertex.h"
#include "bakr/predicates.h"
#include "bakr/predicates_vertex.h"


#include <iostream>

namespace bakr {

using HashMap = std::unordered_map<std::pair<const IntPoint*, const IntPoint*>, size_t, boost::hash<std::pair<const IntPoint*, const IntPoint*>>>;

using EarVertex = Vertex<bool>;


// std::vector<EarVertex> make_vertices(const std::vector<IntPoint>& polygon) {
//   std::vector<EarVertex> vertices(polygon.size(), EarVertex());
//   vertices.front().previous = &vertices.back();
//   vertices.front().point = &polygon.front();
//   vertices.front().next = &vertices[1];
//   for (size_t i=1; i+1<vertices.size(); ++i) {
//     vertices[i].previous = &vertices[i-1];
//     vertices[i].point = &polygon[i];
//     vertices[i].next = &vertices[i+1];
//   }
//   vertices.back().previous = &vertices.back() - 1;
//   vertices.back().point = &polygon.back();
//   vertices.back().next = &vertices.front();

//   for (auto& v: vertices) {
//     v.data = predicate::is_ear(v.raw());
//   }
//   return vertices;
// }

// std::vector<EmptyVertex>::const_iterator find_xmax(std::vector<EmptyVertex>& vertices) {
//   std::vector<EmptyVertex>::const_iterator vmax = vertices.begin();
//   for (; vmax!=vertices.end(); ++vmax) {
//   return vmax;
// }

std::vector<IntPoint>::const_iterator xmax_vertex(const std::vector<IntPoint>& polygon) {
  return std::max_element(polygon.begin(), polygon.end(), 
      [](const IntPoint& p0, const IntPoint& p1) -> bool {return p0.X < p1.X;});
}

std::vector<IntPoint*>::const_iterator xmax_vertex(const std::vector<IntPoint*>& polygon) {
  return std::max_element(polygon.begin(), polygon.end(), 
      [](const IntPoint* p0, const IntPoint* p1) -> bool {return p0->X < p1->X;});
}

const EmptyVertex* xmax_vertex(const std::vector<EmptyVertex>& vertex_polygon) {
  return &(*std::max_element(vertex_polygon.begin(), vertex_polygon.end(), 
      [](const EmptyVertex& v0, const EmptyVertex& v1) -> bool {return v0.point->X < v1.point->X;}));
}

std::vector<const IntPoint*> connect_polygon_with_hole(const std::vector<const IntPoint*>& boundary, const std::vector<IntPoint>& hole) {
  size_t n = boundary.size() + hole.size() + 2;
  std::vector<const IntPoint*> result;
  result.reserve(n);

  std::vector<IntPoint>::const_iterator v_hole = xmax_vertex(hole);
  std::vector<const IntPoint*>::const_iterator v_boundary = boundary.begin();

  for (; v_boundary!=boundary.end(); ++v_boundary) {
    if ((*v_boundary)->X > (*v_hole).X && predicate::is_visible(*v_boundary, &(*v_hole), boundary)) {
      break;
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

void connect_or_store_edge(const IntPoint* a, const IntPoint* b, size_t tree_vertex, TriangleTree& triangle_tree, HashMap& open_edges) {
  std::pair<const IntPoint*, const IntPoint*> edge;
  if (a>b) {
    edge = {a, b};
  } else {
    edge = {b, a};
  }
  auto search_result = open_edges.find(edge);
  if (search_result==open_edges.end()) {
    open_edges.insert({edge, tree_vertex});
  } else {
    boost::add_edge(std::get<1>(*search_result), tree_vertex, triangle_tree);
    open_edges.erase(search_result);
  }
}

namespace triangulation {

namespace graph {

TriangleTree ear_clipping(std::vector<EarVertex> vertices) {
  for (auto& v: vertices) {
    v.data = predicate::is_ear(v.raw());
    std::cout << v.data << std::endl;
  }

  HashMap open_edges;

  EarVertex* current_vertex = &vertices.front();
  size_t N = vertices.size();
  TriangleTree triangle_tree;
  while (N>3) {
    // Find next ear
    if (!current_vertex->data) {
      EarVertex* v = current_vertex->next;
      while (!v->data) {
        assert(v!=current_vertex);
        v = v->next;
      }
      current_vertex = v;
    }

    // Add ear to tree
    Triangle triangle {current_vertex->previous->point, current_vertex->point, current_vertex->next->point};
    size_t tree_vertex = boost::add_vertex(triangle, triangle_tree);
    connect_or_store_edge(triangle[0], triangle[1], tree_vertex, triangle_tree, open_edges);
    connect_or_store_edge(triangle[1], triangle[2], tree_vertex, triangle_tree, open_edges);
    connect_or_store_edge(triangle[2], triangle[0], tree_vertex, triangle_tree, open_edges);

    // Remove ear and recalculate possibly changed earness
    N -= 1;
    remove_vertex(current_vertex);
    current_vertex->previous->data = predicate::is_ear(current_vertex->previous->raw());
    current_vertex->next->data = predicate::is_ear(current_vertex->next->raw());
    current_vertex = current_vertex->next;
  }
  Triangle triangle {current_vertex->previous->point, current_vertex->point, current_vertex->next->point};
  size_t tree_vertex = boost::add_vertex(triangle, triangle_tree);
  connect_or_store_edge(triangle[0], triangle[1], tree_vertex, triangle_tree, open_edges);
  connect_or_store_edge(triangle[1], triangle[2], tree_vertex, triangle_tree, open_edges);
  connect_or_store_edge(triangle[2], triangle[0], tree_vertex, triangle_tree, open_edges);
  return triangle_tree;
}

TriangleTree ear_clipping(const std::vector<IntPoint>& polygon) {
  return ear_clipping(make_vertices<bool>(polygon));
}

TriangleTree ear_clipping(const std::vector<const IntPoint*>& polygon) {
  return ear_clipping(make_vertices<bool>(polygon));
}

} // namespace graph

} // namespace triangulation


std::vector<std::array<IntPoint, 3>> triangles(const TriangleTree& tree) {
  std::vector<std::array<IntPoint, 3>> result;
  boost::graph_traits<TriangleTree>::vertex_iterator vi, vi_end;
  for (boost::tie(vi, vi_end) = boost::vertices(tree); vi != vi_end; ++vi) {
    const Triangle& t = tree[*vi];
    result.push_back({*std::get<0>(t), *std::get<1>(t), *std::get<2>(t)});
  }
  return result;
}

} // namespace bakr
