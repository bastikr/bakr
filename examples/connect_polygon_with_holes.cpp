#include "bakr.h"

#include "wigeon/wigeon.h"
#include <fstream>
#include <iostream>

using namespace bakr;

std::vector<IntPoint> collect(const std::vector<const IntPoint*>& vertices) {
  std::vector<IntPoint> result;
  result.reserve(vertices.size());
  std::transform(vertices.begin(), vertices.end(), std::back_inserter(result), [](const IntPoint* v) {return *v;});
  return result;
}

int main() {
  std::vector<IntPoint> polygon {{0, 0}, {10, 0}, {10, 10}, {0, 10}};
  std::vector<IntPoint> hole0 {{6, 2}, {7, 3}, {8, 2}};
  std::vector<IntPoint> hole1 {{4, 1}, {4, 9}, {5, 9}, {5, 1}};
  // std::vector<std::vector<IntPoint>> holes {hole0, hole1};
  std::vector<IntPoint> hole2 {{1, 2}, {2, 3}, {2, 2}};
  // std::vector<std::vector<IntPoint>> holes {hole0, hole1, hole2};
  std::vector<IntPoint> hole3 {{1, 4}, {1, 8}, {2, 4}};
  std::vector<std::vector<IntPoint>> holes {hole0, hole1, hole2, hole3};
  std::vector<const IntPoint*> result = connect_polygon_with_holes(polygon, holes);
  wigeon::Polygon2D wresult;
  for (auto& p: result) {
    wresult.push_back(p->X, p->Y);
  }
  TriangleTree tree = triangulation::graph::ear_clipping(result);

  std::ofstream f;
  f.open ("image.svg");
  wigeon::svg::print_header(f, wigeon::svg::Properties().add("viewBox", "-1 -1 12 12"));

  wigeon::svg::Properties properties_path;
  properties_path
    .add("fill", "none")
    .add("stroke", "#333333")
    .add("stroke-width", "0.05");

  wigeon::svg::print(f, wresult, properties_path);

  // wigeon::svg::Properties properties_triangle;
  // properties_triangle
  //   .add("fill", "none")
  //   .add("stroke", "#bb3333")
  //   .add("stroke-width", "0.04");
  // for (const auto& triangle: triangles(tree)) {
  //   wigeon::Triangle2D wtriangle({triangle[0].X, triangle[0].Y}, {triangle[1].X, triangle[1].Y}, {triangle[2].X, triangle[2].Y});
  //   wigeon::svg::print(f, wtriangle, properties_triangle);
  // }

  wigeon::svg::print_footer(f);
  f.close();
}
