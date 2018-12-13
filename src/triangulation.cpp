#include <array>
#include <unordered_map>
#include <boost/graph/adjacency_list.hpp>


namespace bakr {

struct IntPoint {
  int X;
  int Y;
};

struct Vertex {
  Vertex* previous;
  Vertex* next;

  const IntPoint* point;
  bool is_ear;
};

bool is_ear(const std::vector<IntPoint>& polygon, const std::vector<IntPoint>::const_iterator a);

std::vector<Vertex> make_vertices(const std::vector<IntPoint>& polygon) {
  std::vector<Vertex> vertices(polygon.size(), Vertex());
  vertices.front().previous = &vertices.back();
  vertices.back().next = &vertices.front();
  for (size_t i=0; i<vertices.size(); ++i) {
    vertices[i].point = &polygon[i];
    vertices[i].is_ear = is_ear(polygon, polygon.begin() + i);
    if (i>0) {
      vertices[i].previous = &vertices[i-1];
    }
    if (i+1<vertices.size()) {
      vertices[i].next = &vertices[i+1];
    }
  }
  return vertices;
}

Vertex* remove_vertex(Vertex* vertex) {
  vertex->previous->next = vertex->next;
  vertex->next->previous = vertex->previous;
  return vertex->next;
}

// using IntPoint = ClipperLib::IntPoint;
using Triangle = std::array<const IntPoint*, 3>;
using TriangleTree = boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, Triangle>;

int sign(double x) {
  return (int)((x>0) - (x<0));
}

int orientation(const IntPoint& a, const IntPoint& b, const IntPoint& c) {
  return sign((b.X - a.X) * (c.Y - a.Y) - (c.X - a.X) * (b.Y - a.Y));
}

bool is_collinear(const IntPoint& a, const IntPoint& b, const IntPoint& c) {
  return (b.X - a.X) * (c.Y - a.Y) == (c.X - a.X) * (b.Y - a.Y);
}

bool is_left(const IntPoint& a, const IntPoint& b, const IntPoint& c) {
  return (b.X - a.X) * (c.Y - a.Y) > (c.X - a.X) * (b.Y - a.Y);
}

bool is_left_or_on(const IntPoint& a, const IntPoint& b, const IntPoint& c) {
  return (b.X - a.X) * (c.Y - a.Y) >= (c.X - a.X) * (b.Y - a.Y);
}

bool is_right(const IntPoint& a, const IntPoint& b, const IntPoint& c) {
  return (b.X - a.X) * (c.Y - a.Y) < (c.X - a.X) * (b.Y - a.Y);
}

bool is_intersecting_properly(const IntPoint& a, const IntPoint& b, const IntPoint& c, const IntPoint& d) {
  if (is_collinear(a, b, c) || is_collinear(a, b, d) || is_collinear(c, d, a) || is_collinear(c, d, b)) {
    return false;
  }
  return (is_left(a, b, c) ^ is_left(a, b, d)) && (is_left(c, d, a) ^ is_left(c, d, b));
}

bool is_between(const IntPoint& a, const IntPoint& b, const IntPoint& c) {
  if (!is_collinear(a, b, c)) {
    return false;
  }
  if (a.X != b.X) {
    return ((a.X <= c.X) && (c.X <= b.X)) || ((b.X <= c.X) && (c.X <= a.X));
  } else {
    return ((a.Y <= c.Y) && (c.Y <= b.Y)) || ((b.Y <= c.Y) && (c.Y <= a.Y));
  }
}

bool is_intersecting(const IntPoint& a, const IntPoint& b, const IntPoint& c, const IntPoint& d) {
  if (is_intersecting_properly(a, b, c, d)) {
    return true;
  }
  return is_between(a, b, c) || is_between(a, b, d) || is_between(c, d, a) || is_between(c, d, b);
}

bool is_visible(const std::vector<IntPoint>& polygon, const std::vector<IntPoint>::const_iterator a, const std::vector<IntPoint>::const_iterator b) {
  std::vector<IntPoint>::const_iterator i0 = polygon.end() - 1;
  std::vector<IntPoint>::const_iterator i1 = polygon.begin();
  while (i1!=polygon.end()) {
    if (i0!=a && i0!=b && i1!=a && i1!=b && is_intersecting(*a, *b, *i0, *i1)) {
      return false;
    }
    i0 = i1;
    i1 += 1;
  }
  return true;
}

bool is_visible(const Vertex* a, const Vertex* b) {
  Vertex* i0 = a->next;
  Vertex* i1 = i0->next;
  while (i1!=a) {
    if (i0!=a && i0!=b && i1!=a && i1!=b && is_intersecting(*a->point, *b->point, *i0->point, *i1->point)) {
      return false;
    }
    i0 = i1;
    i1 = i1->next;
  }
  return true;
}


bool is_in_cone(const IntPoint& a0, const IntPoint& a1, const IntPoint& a2, const IntPoint& b) {
  if (is_left_or_on(a1, a2, a0)) {
    return is_left(a1, b, a0) && is_right(a1, b, a2);
  }
  return !(is_left_or_on(a1, b, a2) && is_left_or_on(b, a1, a0));
}

std::vector<IntPoint>::const_iterator next_wrapped(const std::vector<IntPoint>& polygon, const std::vector<IntPoint>::const_iterator a) {
  if (a+1==polygon.end()) {
    return polygon.begin();
  }
  return a + 1;
}

std::vector<IntPoint>::const_iterator previous_wrapped(const std::vector<IntPoint>& polygon, const std::vector<IntPoint>::const_iterator a) {
  if (a==polygon.begin()) {
    return polygon.end() - 1;
  }
  return a - 1;
}

bool is_diagonal(const std::vector<IntPoint>& polygon, const std::vector<IntPoint>::const_iterator a, const std::vector<IntPoint>::const_iterator b) {
  return is_in_cone(*previous_wrapped(polygon, a), *a, *next_wrapped(polygon, a), *b)
      && is_in_cone(*previous_wrapped(polygon, b), *b, *next_wrapped(polygon, b), *a)
      && is_visible(polygon, a, b);
}

bool is_diagonal(const Vertex* a, const Vertex* b) {
  return is_in_cone(*a->previous->point, *a->point, *a->next->point, *b->point)
      && is_in_cone(*b->previous->point, *b->point, *b->next->point, *a->point)
      && is_visible(a, b);
}

bool is_ear(const std::vector<IntPoint>& polygon, const std::vector<IntPoint>::const_iterator a) {
  return is_diagonal(polygon, previous_wrapped(polygon, a), next_wrapped(polygon, a));
}

bool is_ear(const Vertex* a) {
  return is_diagonal(a->previous, a->next);
}

// std::vector<IntPoint>::const_iterator select_ear(const std::vector<IntPoint>& polygon, const std::vector<bool>& is_ear, )

size_t wrap_left(size_t i, size_t delta, size_t N) {
  if (delta<=i) {
    return i - delta;
  }
  return N - delta + i;
}

size_t wrap_right(size_t i, size_t delta, size_t N) {
  if (i+delta>=N) {
    return i + delta - N;
  }
  return i + delta;
}

using HashMap = std::unordered_map<std::pair<const IntPoint*, const IntPoint*>, size_t, boost::hash<std::pair<const IntPoint*, const IntPoint*>>>;

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

TriangleTree triangulate(const std::vector<IntPoint>& polygon) {
  std::vector<Vertex> vertices = make_vertices(polygon);
  HashMap open_edges;

  Vertex* current_vertex = &vertices.front();
  size_t N = polygon.size();
  TriangleTree triangle_tree;
  while (N>3) {
    // Find next ear
    while (!current_vertex->is_ear) {
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
    current_vertex->previous->is_ear = is_ear(current_vertex->previous);
    current_vertex->next->is_ear = is_ear(current_vertex->next);
    current_vertex = current_vertex->next;
  }
  Triangle triangle {current_vertex->previous->point, current_vertex->point, current_vertex->next->point};
  size_t tree_vertex = boost::add_vertex(triangle, triangle_tree);
  connect_or_store_edge(triangle[0], triangle[1], tree_vertex, triangle_tree, open_edges);
  connect_or_store_edge(triangle[1], triangle[2], tree_vertex, triangle_tree, open_edges);
  connect_or_store_edge(triangle[2], triangle[0], tree_vertex, triangle_tree, open_edges);
  return triangle_tree;
}

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
