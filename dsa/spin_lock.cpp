#include <benchmark/benchmark.h>
#include <emmintrin.h>
#include <pthread.h>
#include <sched.h>

#include <atomic>
#include <cstdint>
#include <new>

namespace {

class SpinLockV1 {
  std::atomic_bool locked_{false};

public:
  auto lock() noexcept -> void { while (locked_.exchange(true)); }
  auto unlock() noexcept -> void { locked_.store(false); }
};

class SpinLockV2 {
  std::atomic_bool locked_{false};

public:
  auto lock() noexcept -> void {
    while (locked_.exchange(true, std::memory_order_acquire));
  }
  auto unlock() noexcept -> void {
    locked_.store(false, std::memory_order_release);
  }
};

class SpinLockV3 {
  std::atomic_bool locked_{false};

public:
  auto lock() noexcept -> void {
    while (locked_.exchange(true, std::memory_order_acquire)) {
      while (locked_.load(std::memory_order_relaxed)) {  // Read-only spin
        _mm_pause();                                     // Backoff
      }
    }
  }
  auto unlock() noexcept -> void {
    locked_.store(false, std::memory_order_release);
  }
};

class SpinLockV4 {
  std::atomic_bool locked_{false};

public:
  auto lock() noexcept -> void {
    auto backoff = 1;
    while (locked_.exchange(true, std::memory_order_acquire)) {
      do {
        for (auto i = 0; i < backoff; ++i) _mm_pause();  // Backoff
        backoff = backoff < 64 ? backoff << 1 : 64;      // Exp. growth
      } while (locked_.load(std::memory_order_relaxed));  // Read-only spin
    }
  }
  auto unlock() noexcept -> void {
    locked_.store(false, std::memory_order_release);
  }
};

auto pinThread(int cpu) noexcept -> void {
  auto cpuset = cpu_set_t{};
  CPU_ZERO(&cpuset);
  CPU_SET(cpu, &cpuset);
  pthread_setaffinity_np(pthread_self(), sizeof(cpuset), &cpuset);
}

template <typename Lockable>
auto BM_SpinLock(benchmark::State& state) -> void {
  alignas(std::hardware_destructive_interference_size) static auto lockable =
      Lockable{};
  alignas(std::hardware_destructive_interference_size) static auto counter =
      std::uint64_t{};

  pinThread(state.thread_index());
  for (auto _ : state) {
    lockable.lock();
    ++counter;
    lockable.unlock();
  }
  benchmark::DoNotOptimize(counter);
}

}  // namespace

BENCHMARK(BM_SpinLock<SpinLockV1>)
    ->ThreadRange(1, 4)
    ->UseRealTime()
    ->Iterations(1'000'000);

BENCHMARK(BM_SpinLock<SpinLockV2>)
    ->ThreadRange(1, 4)
    ->UseRealTime()
    ->Iterations(1'000'000);

BENCHMARK(BM_SpinLock<SpinLockV3>)
    ->ThreadRange(1, 4)
    ->UseRealTime()
    ->Iterations(1'000'000);

BENCHMARK(BM_SpinLock<SpinLockV4>)
    ->ThreadRange(1, 4)
    ->UseRealTime()
    ->Iterations(1'000'000);
