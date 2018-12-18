#include "bakr.h"

#include "wigeon/wigeon.h"
#include <fstream>
#include <iostream>

using namespace bakr;

int main() {
  // std::vector<IntPoint> polygon {{0, 0}, {1, 1}, {4, 5}, {10, 0}, {6, 10}, {0, 5}};
  std::vector<IntPoint> p0 {{0, 0}, {10, 0}, {5, 10}};
  std::vector<IntPoint> p1 {{6, 1}, {4, 1}, {5, 3}};
  std::vector<const IntPoint*> polygon {&p0[0], &p0[1], &p0[2], &p0[0], &p1[0], &p1[1], &p1[2], &p1[0]};

  TriangleTree tree = triangulation::graph::ear_clipping(polygon);

  std::ofstream f;
  f.open ("image.svg");
  wigeon::svg::print_header(f, wigeon::svg::Properties().add("viewBox", "0 0 10 10"));

  wigeon::svg::Properties properties_path;
  properties_path
    .add("fill", "none")
    .add("stroke", "#333333")
    .add("stroke-width", "0.03");

  for (const auto& triangle: triangles(tree)) {
    wigeon::Triangle2D wtriangle({triangle[0].X, triangle[0].Y}, {triangle[1].X, triangle[1].Y}, {triangle[2].X, triangle[2].Y});
    wigeon::svg::print(f, wtriangle, properties_path);
  }

  wigeon::svg::print_footer(f);
  f.close();
}
