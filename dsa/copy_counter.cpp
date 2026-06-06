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

auto UseObjectWithCopy(Object /*object*/) noexcept {};
auto UseObjectNoCopy(const Object& /*object*/) noexcept {};

TEST(CopyCounter, DoesCopy) {
  // Arrange
  Object::copy_count = 0;
  auto object = Object{};

  // Act
  UseObjectWithCopy(object);

  // Assert
  EXPECT_EQ(1, Object::copy_count);
}

TEST(CopyCounter, DoesNotCopy) {
  // Arrange
  Object::copy_count = 0;
  auto object = Object{};

  // Act
  UseObjectNoCopy(object);

  // Assert
  EXPECT_EQ(0, Object::copy_count);
}
