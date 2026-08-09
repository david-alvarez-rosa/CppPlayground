#include <benchmark/benchmark.h>
#include <immintrin.h>
#include <pthread.h>
#include <sched.h>

#include <atomic>
#include <cstdint>
#include <cstdlib>
#include <mutex>
#include <thread>
#include <vector>

namespace {

class SpinLockV0 {
  std::mutex mutex_;

public:
  auto lock() -> void { mutex_.lock(); }
  auto unlock() noexcept -> void { mutex_.unlock(); }
};

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
    auto mask = 64;
    while (locked_.exchange(true, std::memory_order_acquire)) {
      do {
        for (auto i = 0; i < mask; ++i) _mm_pause();      // Backoff
        mask = mask < 1024 ? mask << 1 : 1024;            // Exp. growth
      } while (locked_.load(std::memory_order_relaxed));  // Read-only
    }
  }
  auto unlock() noexcept -> void {
    locked_.store(false, std::memory_order_release);
  }
};

auto pinThread(int cpu_id) noexcept -> void {
  cpu_set_t cpuset;
  CPU_ZERO(&cpuset);
  CPU_SET(cpu_id, &cpuset);
  if (pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset) != 0)
      [[unlikely]] {
    std::exit(EXIT_FAILURE);
  }
}

template <typename SpinLock>
auto BM_SpinLock(benchmark::State& state) -> void {
  constexpr auto num_increments = 250'000U;
  const auto num_threads = state.range(0);

  auto spin_lock = SpinLock{};
  auto val = std::uint64_t{};
  auto threads = std::vector<std::thread>{};
  threads.reserve(num_threads);

  for (auto _ : state) {
    for (auto i = 0U; i < num_threads; ++i) {
      threads.emplace_back([&, i] {
        pinThread(i);
        for (auto j = 0U; j < num_increments / num_threads; ++j) {
          spin_lock.lock();
          ++val;
          spin_lock.unlock();
        }
      });
    }
    for (auto& thread : threads) thread.join();
    benchmark::DoNotOptimize(val);
    threads.clear();
  }
}

}  // namespace

BENCHMARK(BM_SpinLock<SpinLockV0>)
    ->RangeMultiplier(2)
    ->Range(1, 4)
    ->UseRealTime()
    ->Unit(benchmark::kMillisecond);

BENCHMARK(BM_SpinLock<SpinLockV1>)
    ->RangeMultiplier(2)
    ->Range(1, 4)
    ->UseRealTime()
    ->Unit(benchmark::kMillisecond);

BENCHMARK(BM_SpinLock<SpinLockV2>)
    ->RangeMultiplier(2)
    ->Range(1, 4)
    ->UseRealTime()
    ->Unit(benchmark::kMillisecond);

BENCHMARK(BM_SpinLock<SpinLockV3>)
    ->RangeMultiplier(2)
    ->Range(1, 4)
    ->UseRealTime()
    ->Unit(benchmark::kMillisecond);

BENCHMARK(BM_SpinLock<SpinLockV4>)
    ->RangeMultiplier(2)
    ->Range(1, 4)
    ->UseRealTime()
    ->Unit(benchmark::kMillisecond);
