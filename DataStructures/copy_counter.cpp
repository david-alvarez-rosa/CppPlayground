#include <gtest/gtest.h>

template <typename Derived>
struct CopyCounter {
  static int copy_count;

  CopyCounter() noexcept = default;
  ~CopyCounter() noexcept = default;
  CopyCounter(const CopyCounter& /*other*/) noexcept { ++copy_count; }
  CopyCounter(CopyCounter&&) noexcept = default;
  auto operator=(const CopyCounter& /*other*/) noexcept -> CopyCounter& {
    ++copy_count;
    return *this;
  }
  auto operator=(CopyCounter&&) noexcept -> CopyCounter& = default;
};

template <typename Derived>
auto CopyCounter<Derived>::copy_count = 0;

struct Object : public CopyCounter<Object> {};

auto UseObject(const Object& /*object*/) noexcept {};

TEST(CopyCounter, BasicCount) {
  auto object = Object{};
  UseObject(object);
  EXPECT_EQ(0, Object::copy_count);
}
