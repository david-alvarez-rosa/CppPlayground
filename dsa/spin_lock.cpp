#include <benchmark/benchmark.h>
#include <emmintrin.h>
#include <pthread.h>
#include <sched.h>

#include <atomic>
#include <cstdint>
#include <mutex>

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

template <typename Lock>
auto BM_SpinLock(benchmark::State& state) -> void {
  static auto lock = Lock{};
  static auto val = std::uint64_t{};

  pinThread(state.thread_index());
  for (auto _ : state) {
    lock.lock();
    ++val;
    lock.unlock();
  }
  benchmark::DoNotOptimize(val);
}

}  // namespace

BENCHMARK(BM_SpinLock<SpinLockV0>)->ThreadRange(1, 4)->UseRealTime();
BENCHMARK(BM_SpinLock<SpinLockV1>)->ThreadRange(1, 4)->UseRealTime();
BENCHMARK(BM_SpinLock<SpinLockV2>)->ThreadRange(1, 4)->UseRealTime();
BENCHMARK(BM_SpinLock<SpinLockV3>)->ThreadRange(1, 4)->UseRealTime();
BENCHMARK(BM_SpinLock<SpinLockV4>)->ThreadRange(1, 4)->UseRealTime();
