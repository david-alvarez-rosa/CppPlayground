#include <benchmark/benchmark.h>

static void bench(benchmark::State& state) {
  for (auto _ : state) {
  }
}

BENCHMARK(bench);
