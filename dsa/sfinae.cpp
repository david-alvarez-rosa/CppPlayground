#include <gtest/gtest.h>

#include <string>
#include <type_traits>

template <typename T>
class HasFoo {
  template <typename U>
  static auto Test(int) -> decltype(std::declval<U>().foo(), std::true_type{});
  template <typename>
  static std::false_type Test(...);

 public:
  static constexpr bool value = decltype(Test<T>(0))::value;
};

struct A {
  static auto foo() noexcept -> std::string { return "A::foo()"; }
};
struct B {};

template <typename T>
typename std::enable_if<HasFoo<T>::value, std::string>::type Check(T t) {
  return t.foo();
}

template <typename T>
typename std::enable_if<!HasFoo<T>::value, std::string>::type Check(T) {
  return "No foo!";
}

TEST(HasFoo, FooExists) { EXPECT_EQ(Check(A{}), "A::foo()"); }
TEST(HasFoo, FooDoesNotExist) { EXPECT_EQ(Check(B{}), "No foo!"); }
