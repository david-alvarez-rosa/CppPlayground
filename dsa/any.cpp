#include <gtest/gtest.h>

#include <memory>

class Any {
  class Concept {
   public:
    virtual ~Concept() = default;
    virtual auto f() const noexcept -> void = 0;
  };

  template <typename T>
  class Model : public Concept {
    std::unique_ptr<T> obj_;

   public:
    explicit Model(T obj) noexcept
        : obj_{std::make_unique<T>(std::move(obj))} {}
    auto f() const noexcept -> void override { obj_->f(); }
  };

  std::unique_ptr<Concept> obj_;

 public:
  template <typename T>
  explicit Any(T&& obj) noexcept
      : obj_{std::make_unique<Model<T>>(std::forward<T>(obj))} {}

  auto f() const noexcept -> void { obj_->f(); }
};

namespace test {

template <typename Derived>
struct NoCopyChecker {
  static int copy_count;

  explicit NoCopyChecker() noexcept = default;
  ~NoCopyChecker() noexcept = default;
  NoCopyChecker(const NoCopyChecker& /*unused*/) { ++copy_count; };
  NoCopyChecker(NoCopyChecker&&) noexcept = default;
  auto operator=(const NoCopyChecker& /*unused*/) noexcept -> NoCopyChecker& {
    ++copy_count;
    return *this;
  }
  auto operator=(NoCopyChecker&&) noexcept -> NoCopyChecker& = default;
};

template <typename Derived>
auto NoCopyChecker<Derived>::copy_count = 0;

struct ElementA : public NoCopyChecker<ElementA> {
  explicit ElementA() noexcept = default;
  auto f() const noexcept -> void {};
};

struct ElementB : public NoCopyChecker<ElementB> {
  explicit ElementB() noexcept = default;
  auto f() const noexcept -> void {};
};

TEST(Any, CanBePutInAVector) {
  auto elements = std::vector<Any>{};
  elements.reserve(2);
  elements.emplace_back(ElementA{});
  elements.emplace_back(ElementB{});
}

TEST(Any, CallUnderlyingMethod) {
  auto elements = std::vector<Any>{};
  elements.reserve(2);
  elements.emplace_back(ElementA{});
  elements.emplace_back(ElementB{});

  for (const auto& element : elements) {
    element.f();
  }
}

TEST(Any, NoCopiesAreMade) {
  auto elements = std::vector<Any>{};
  elements.reserve(2);
  ElementA::copy_count = 0;
  ElementB::copy_count = 0;

  elements.emplace_back(ElementA{});
  elements.emplace_back(ElementB{});

  EXPECT_EQ(0, ElementA::copy_count);
  EXPECT_EQ(0, ElementB::copy_count);
}

}  // namespace test
