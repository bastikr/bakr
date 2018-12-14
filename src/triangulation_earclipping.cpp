#include "bakr/triangulation_earclipping.h"

#include <unordered_map>

#include "bakr/vertex.h"
#include "bakr/predicates.h"
#include "bakr/predicates_vertex.h"


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

TriangleTree ear_clipping(const std::vector<IntPoint>& polygon) {
  std::vector<EarVertex> vertices = make_vertices<bool>(polygon);
  for (auto& v: vertices) {
    v.data = predicate::is_ear(v.raw());
  }

  HashMap open_edges;

  EarVertex* current_vertex = &vertices.front();
  size_t N = polygon.size();
  TriangleTree triangle_tree;
  while (N>3) {
    // Find next ear
    while (!current_vertex->data) {
      current_vertex = current_vertex->next;
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
