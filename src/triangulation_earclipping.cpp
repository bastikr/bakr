#include "bakr/triangulation_earclipping.h"

#include <unordered_map>

#include "bakr/vertex.h"
#include "bakr/predicates.h"
#include "bakr/predicates_vertex.h"


namespace bakr {

using HashMap = std::unordered_map<
  std::pair<const IntPoint*, const IntPoint*>,
  std::pair<size_t, size_t>,
  boost::hash<std::pair<const IntPoint*, const IntPoint*>>>;

using EarVertex = Vertex<bool>;


void connect_or_store_edge(const IntPoint* a, const IntPoint* b, size_t triangle_edge, size_t tree_vertex, TriangleTree& triangle_tree, HashMap& open_edges) {
  auto search_result = open_edges.find({b, a});
  if (search_result==open_edges.end()) {
    open_edges.insert({{a, b}, {tree_vertex, triangle_edge}});
  } else {
    size_t other_triangle_edge, other_tree_vertex;
    boost::tie(other_tree_vertex, other_triangle_edge) = std::get<1>(*search_result);
    boost::add_edge(other_tree_vertex, tree_vertex, {other_triangle_edge, triangle_edge}, triangle_tree);
    open_edges.erase(search_result);
  }
}

void connect_or_store_edges(const Triangle& triangle, size_t tree_vertex, TriangleTree& triangle_tree, HashMap& open_edges) {
  connect_or_store_edge(triangle[0], triangle[1], 0, tree_vertex, triangle_tree, open_edges);
  connect_or_store_edge(triangle[1], triangle[2], 1, tree_vertex, triangle_tree, open_edges);
  connect_or_store_edge(triangle[2], triangle[0], 2, tree_vertex, triangle_tree, open_edges);
}

void add_triangle(const EarVertex* current_vertex, TriangleTree& triangle_tree, HashMap& open_edges) {
  Triangle triangle {current_vertex->previous->point, current_vertex->point, current_vertex->next->point};
  size_t tree_vertex = boost::add_vertex(triangle, triangle_tree);
  connect_or_store_edges(triangle, tree_vertex, triangle_tree, open_edges);
}

namespace triangulation {

namespace graph {

TriangleTree ear_clipping(std::vector<EarVertex> vertices) {
  for (auto& v: vertices) {
    v.data = predicate::is_ear(v.raw());
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
    add_triangle(current_vertex, triangle_tree, open_edges);

    // Remove ear and recalculate possibly changed earness
    N -= 1;
    remove_vertex(current_vertex);
    current_vertex->previous->data = predicate::is_ear(current_vertex->previous->raw());
    current_vertex->next->data = predicate::is_ear(current_vertex->next->raw());
    current_vertex = current_vertex->next;
  }
  // Add remaining three points
  add_triangle(current_vertex, triangle_tree, open_edges);

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
