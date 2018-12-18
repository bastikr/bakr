#include "bakr.h"

#include "wigeon/wigeon.h"
#include <fstream>
#include <iostream>

using namespace bakr;


int main() {
  std::vector<IntPoint> comb = construct::comb(4);
  wigeon::Polygon2D wresult;
  for (auto& p: comb) {
    wresult.push_back(p.X, p.Y);
  }

  std::ofstream f;
  f.open ("image.svg");
  wigeon::svg::print_header(f, wigeon::svg::Properties().add("viewBox", "-1 -1 12 12"));

  wigeon::svg::Properties properties_path;
  properties_path
    .add("fill", "none")
    .add("stroke", "#333333")
    .add("stroke-width", "0.05");

  wigeon::svg::print(f, wresult, properties_path);

  wigeon::svg::print_footer(f);
  f.close();
}
