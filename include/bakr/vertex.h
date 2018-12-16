#pragma once

#include <tuple>
#include <vector>

#include "bakr/intpoint.h"


namespace bakr {

template<typename T>
struct Vertex {
  Vertex<T>* previous;
  Vertex<T>* next;

  Vertex<std::tuple<>>* raw() {
    return reinterpret_cast<Vertex<std::tuple<>>*>(this);
  }

  const IntPoint* point;
  T data;
};

using EmptyVertex = Vertex<std::tuple<>>;

template<typename T>
Vertex<T>* remove_vertex(Vertex<T>* vertex) {
  vertex->previous->next = vertex->next;
  vertex->next->previous = vertex->previous;
  return vertex->next;
}

template<typename T>
std::vector<Vertex<T>> make_vertices(const std::vector<IntPoint>& polygon) {
  std::vector<Vertex<T>> vertices(polygon.size(), Vertex<T>());
  vertices.front().previous = &vertices.back();
  vertices.front().point = &polygon.front();
  vertices.front().next = &vertices[1];
  for (size_t i=1; i+1<vertices.size(); ++i) {
    vertices[i].previous = &vertices[i-1];
    vertices[i].point = &polygon[i];
    vertices[i].next = &vertices[i+1];
  }
  vertices.back().previous = &vertices.back() - 1;
  vertices.back().point = &polygon.back();
  vertices.back().next = &vertices.front();
  return vertices;
}

} // namespace bakr
