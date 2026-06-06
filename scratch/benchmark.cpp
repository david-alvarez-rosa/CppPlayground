#include <benchmark/benchmark.h>

static auto bench(benchmark::State& state) -> void {
  for (auto _ : state) {
  }
}

BENCHMARK(bench);
