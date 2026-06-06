#include <gtest/gtest.h>

#include <atomic>

class MyType {
 public:
  explicit MyType(int num) noexcept : num_{num} {};
  inline auto GetNum() const noexcept -> int { return num_; }
  inline auto SetNum(int num) noexcept -> void { num_ = num; }

 private:
  int num_;
};

template <typename T>
class SharedPtr {
 public:
  explicit SharedPtr() noexcept = default;

  explicit SharedPtr(T* ptr) noexcept
      : ptr_{ptr}, ref_counter_{new std::atomic_uint(1)} {}

  SharedPtr(const SharedPtr& other) noexcept
      : ptr_{other.ptr_}, ref_counter_(other.ref_counter_) {
    IncrementRefCounter();
  }

  SharedPtr(SharedPtr&& other) noexcept
      : ptr_{other.ptr_}, ref_counter_{other.ref_counter_} {
    other.ptr_ = nullptr;
    other.ref_counter_ = nullptr;
  }

  ~SharedPtr() noexcept { DecrementRefCounter(); }

  auto operator=(const SharedPtr& other) noexcept -> SharedPtr& {
    if (this != &other) [[likely]] {
      ptr_ = other.ptr_;
      ref_counter_ = other.ref_counter_;
      IncrementRefCounter();
    }
    return *this;
  }

  auto operator=(SharedPtr&& other) -> SharedPtr& {
    if (this != &other) [[likely]] {
      ptr_ = other.ptr_;
      ref_counter_ = other.ref_counter_;
      other.ptr_ = nullptr;
      other.ref_counter_ = nullptr;
    }
    return *this;
  }

  inline auto Get() const noexcept -> T* { return ptr_; }

  inline auto operator->() const noexcept -> T* { return ptr_; }

  inline auto operator*() const noexcept -> T& { return *ptr_; }

  inline explicit operator bool() const noexcept { return nullptr != ptr_; }

  auto Swap(SharedPtr& other) noexcept -> void {
    std::swap(ptr_, other.ptr_);
    std::swap(ref_counter_, other.ref_counter_);
  }

 private:
  T* ptr_{nullptr};
  std::atomic_uint* ref_counter_{nullptr};

  auto DecrementRefCounter() noexcept -> void {
    if (nullptr != ref_counter_) {
      --(*ref_counter_);
      if (0 == *ref_counter_) {
        delete ref_counter_;
        delete ptr_;
      }
    }
  }

  auto IncrementRefCounter() noexcept -> void {
    if (nullptr != ref_counter_) {
      ++(*ref_counter_);
    }
  }
};

template <typename T>
auto Swap(SharedPtr<T>& lhs, SharedPtr<T>& rhs) -> void {
  lhs.Swap(rhs);
}

template <typename T, typename... Args>
auto MakeShared(Args&&... args) -> SharedPtr<T> {
  // TODO: Allocate memory only once
  // https://github.com/llvm/llvm-project/blob/f01b62ad4881e61dc5d84e1faa984917ac43453c/libcxx/include/__memory/shared_ptr.h#L728
  return SharedPtr<T>(new T(std::forward<Args>(args)...));
}

TEST(SharedPtr, StarOperator) {
  auto shared_ptr = SharedPtr<int>(new int(7));
  ASSERT_EQ(7, *shared_ptr);
}

TEST(SharedPtr, ArrowOperator) {
  auto shared_ptr = SharedPtr<MyType>(new MyType(7));
  ASSERT_EQ(7, shared_ptr->GetNum());
}

TEST(SharedPtr, MakeShared) {
  auto shared_ptr = MakeShared<MyType>(3);
  ASSERT_EQ(3, shared_ptr->GetNum());
}

TEST(SharedPtr, CopyCtor) {
  auto shared_ptr = MakeShared<MyType>(3);
  {
    auto shared_ptr_copy = SharedPtr<MyType>{shared_ptr};
    ASSERT_EQ(3, shared_ptr_copy->GetNum());
  }
  ASSERT_EQ(3, shared_ptr->GetNum());
}

TEST(SharedPtr, MoveCtor) {
  auto shared_ptr = MakeShared<MyType>(3);
  auto shared_ptr_move = SharedPtr<MyType>{std::move(shared_ptr)};
  ASSERT_EQ(3, shared_ptr_move->GetNum());
  shared_ptr_move->SetNum(9);
}

TEST(SharedPtr, CopyAssignment) {
  auto shared_ptr = MakeShared<MyType>(3);
  {
    auto shared_ptr_copy = shared_ptr;
    ASSERT_EQ(3, shared_ptr_copy->GetNum());
    shared_ptr_copy->SetNum(9);
  }
  ASSERT_EQ(9, shared_ptr->GetNum());
}

TEST(SharedPtr, MoveAssignment) {
  auto shared_ptr = MakeShared<MyType>(3);
  {
    auto shared_ptr_move = std::move(shared_ptr);
    ASSERT_EQ(3, shared_ptr_move->GetNum());
    shared_ptr_move->SetNum(9);
  }
  ASSERT_EQ(9, shared_ptr->GetNum());
}
