#include <gtest/gtest.h>

class MyType {
 public:
  explicit MyType(int num) noexcept : num_{num} {};
  int GetNum() const noexcept { return num_; }

 private:
  int num_;
};

template <typename T>
class UniquePtr final {
 public:
  explicit UniquePtr(T* ptr = nullptr) : ptr_{ptr} {}

  ~UniquePtr() { delete ptr_; }

  UniquePtr(const UniquePtr&) = delete;
  UniquePtr& operator=(const UniquePtr&) = delete;

  UniquePtr(UniquePtr&& other) : ptr_{other.ptr_} { other.ptr_ = nullptr; }

  UniquePtr& operator=(UniquePtr&& other) noexcept {
    if (this != &other) {
      delete ptr_;
      ptr_ = other.ptr_;
      other.ptr_ = nullptr;
    }

    return *this;
  }

  T& operator*() const noexcept { return *ptr_; }

  T* Get() const noexcept { return ptr_; }

  T* Release() noexcept {
    auto tmp = ptr_;
    ptr_ = nullptr;
    return tmp;
  }

  void Reset(T* new_ptr = nullptr) noexcept {
    if (ptr_ != new_ptr) {
      delete ptr_;
      ptr_ = new_ptr;
    }
  }

  void Swap(UniquePtr& other) { std::swap(ptr_, other.ptr_); }

  T* operator->() const noexcept { return ptr_; }

  explicit operator bool() const noexcept { return nullptr != ptr_; }

 private:
  T* ptr_;
};

template <typename T>
void Swap(UniquePtr<T>& lhs, UniquePtr<T>& rhs) {
  lhs.Swap(rhs);
}

template <typename T, typename... Args>
UniquePtr<T> MakeUnique(Args&&... args) {
  return UniquePtr<T>(new T(std::forward<Args>(args)...));
}

TEST(UniquePtr, StarOperator) {
  auto unique_ptr = UniquePtr<int>(new int(3));
  ASSERT_EQ(3, *unique_ptr);
}

TEST(UniquePtr, ArrowOperator) {
  auto unique_ptr = UniquePtr<MyType>(new MyType(7));
  ASSERT_EQ(7, unique_ptr->GetNum());
}

TEST(UniquePtr, MakeUnique) {
  auto unique_ptr = MakeUnique<MyType>(3);
  ASSERT_EQ(3, unique_ptr->GetNum());
}
