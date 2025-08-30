#include <gtest/gtest.h>

#include <string>
#include <type_traits>

template <typename T, typename = void>
struct HasFoo : std::false_type {};

template <typename T>
struct HasFoo<T, std::void_t<decltype(std::declval<T>().foo())>> : std::true_type {};

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
