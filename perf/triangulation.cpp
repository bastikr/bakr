#include <benchmark/benchmark.h>

#include "bakr.h"

using namespace bakr;


void BM_triangulate(benchmark::State& state) {
  int N=state.range(0);
  std::vector<IntPoint> polygon;
  polygon.reserve(N + 1);
  for (int i=0; i<N; ++i) {
    polygon.push_back(IntPoint{i, 0});
  }
  polygon.push_back({50, 20});

  for (auto _ : state)
    triangulation::graph::ear_clipping(polygon);
}


BENCHMARK(BM_triangulate)->RangeMultiplier(2)->Range(8, 1024);

BENCHMARK_MAIN();
