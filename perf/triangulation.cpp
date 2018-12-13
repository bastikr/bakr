#include <benchmark/benchmark.h>

#include "src/triangulation.cpp"

using namespace bakr;


void BM_triangulate(benchmark::State& state) {
  int N=state.range(0);
  std::vector<IntPoint> polygon;
  for (int i=0; i<N; ++i) {
    polygon.push_back(IntPoint{i, 0});
  }
  polygon.push_back({50, 20});

  for (auto _ : state)
    triangulate(polygon);
}


BENCHMARK(BM_triangulate)->RangeMultiplier(2)->Range(8, 1024);


BENCHMARK_MAIN();
