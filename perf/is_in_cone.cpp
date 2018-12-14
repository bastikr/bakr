// #include <benchmark/benchmark.h>

// #include "src/triangulation.cpp"

// #include <cstdlib>

// using namespace bakr;


// void BM_is_in_cone(benchmark::State& state) {
//   IntPoint a {rand(), rand()};
//   IntPoint b {rand(), rand()};
//   IntPoint c {rand(), rand()};
//   IntPoint d {rand(), rand()};

//   for (auto _ : state) {
//     for (int i=0; i<1000; ++i) {
//         benchmark::DoNotOptimize(is_in_cone(a, b, c, d));
//         benchmark::DoNotOptimize(is_in_cone(a, b, d, c));
//         benchmark::DoNotOptimize(is_in_cone(a, d, b, c));
//         benchmark::DoNotOptimize(is_in_cone(a, d, c, b));
//         benchmark::DoNotOptimize(is_in_cone(b, a, c, d));
//         benchmark::DoNotOptimize(is_in_cone(b, a, d, c));
//         benchmark::DoNotOptimize(is_in_cone(d, a, b, c));
//         benchmark::DoNotOptimize(is_in_cone(d, a, c, b));
//         benchmark::DoNotOptimize(is_in_cone(b, c, a, d));
//         benchmark::DoNotOptimize(is_in_cone(b, d, a, c));
//         benchmark::DoNotOptimize(is_in_cone(d, b, a, c));
//         benchmark::DoNotOptimize(is_in_cone(d, c, a, b));
//         benchmark::DoNotOptimize(is_in_cone(b, c, d, a));
//         benchmark::DoNotOptimize(is_in_cone(b, d, c, a));
//         benchmark::DoNotOptimize(is_in_cone(d, b, c, a));
//         benchmark::DoNotOptimize(is_in_cone(d, c, b, a));
//     }
//   }
// }

// BENCHMARK(BM_is_in_cone);

// // BENCHMARK_MAIN();
