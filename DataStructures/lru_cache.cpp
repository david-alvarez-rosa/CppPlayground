#include <gtest/gtest.h>

#include <cstddef>
#include <list>
#include <string>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <utility>

template <typename Key, typename Value>
class LruCache {
  using Node = std::pair<Key, Value>;

  std::list<Node> nodes_;
  std::unordered_map<Key, typename std::list<Node>::iterator> index_;
  std::size_t capacity_;

 public:
  explicit LruCache(std::size_t capacity) : capacity_{capacity} {}

  auto Push(const Key& key, Value value) noexcept -> void {
    Emplace(key, std::move(value));
  }

  template <typename... Args>
  auto Emplace(const Key& key, Args&&... args) -> void {
    if (Size() == capacity_) {
      index_.erase(nodes_.back().first);
      nodes_.pop_back();
    }

    if (Contains(key)) {
      nodes_.erase(index_[key]);
      index_.erase(key);
    }

    nodes_.emplace_front(key, std::forward<Args>(args)...);
    index_[key] = nodes_.begin();
  }

  auto Get(const Key& key) noexcept -> const Value& {
    auto it = index_[key];
    nodes_.splice(nodes_.begin(), nodes_, it);
    return it->second;
  }

  [[nodiscard]] auto Size() const noexcept -> std::size_t {
    return nodes_.size();
  }

  [[nodiscard]] auto Contains(const Key& key) const noexcept -> bool {
    return index_.contains(key);
  }
};

TEST(LruCache, CorrectSize) {
  auto lru_cache = LruCache<int, std::string>{2};
  lru_cache.Push(1, "one");
  lru_cache.Push(2, "two");

  EXPECT_EQ(2, lru_cache.Size());
}

TEST(LruCache, ContainsPushedValues) {
  auto lru_cache = LruCache<int, std::string>{2};
  lru_cache.Push(1, "one");
  lru_cache.Push(2, "two");

  EXPECT_EQ("one", lru_cache.Get(1));
  EXPECT_EQ("two", lru_cache.Get(2));
}

TEST(LruCache, DoesNotExceedCapacity) {
  auto lru_cache = LruCache<int, std::string>{2};
  lru_cache.Push(1, "one");
  lru_cache.Push(2, "two");
  lru_cache.Push(3, "three");

  EXPECT_EQ(2, lru_cache.Size());
}

TEST(LruCache, SortLeastRecentlyUsed) {
  auto lru_cache = LruCache<int, std::string>{2};

  lru_cache.Push(1, "one");
  lru_cache.Push(2, "two");
  lru_cache.Push(3, "three");

  EXPECT_FALSE(lru_cache.Contains(1));
  EXPECT_EQ("two", lru_cache.Get(2));
  EXPECT_EQ("three", lru_cache.Get(3));
}

TEST(LruCache, SortLeastRecentlyUsedWhenGetting) {
  auto lru_cache = LruCache<int, std::string>{2};

  lru_cache.Push(1, "one");
  lru_cache.Push(2, "two");
  std::ignore = lru_cache.Get(1);
  lru_cache.Push(3, "three");

  EXPECT_FALSE(lru_cache.Contains(2));
  EXPECT_EQ("one", lru_cache.Get(1));
  EXPECT_EQ("three", lru_cache.Get(3));
}

TEST(LruCache, ResortsWhenPushingExistingKey) {
  auto lru_cache = LruCache<int, std::string>{2};

  lru_cache.Push(1, "one");
  lru_cache.Push(2, "two");
  lru_cache.Push(1, "new one");
  lru_cache.Push(3, "three");

  EXPECT_FALSE(lru_cache.Contains(2));
  EXPECT_EQ("new one", lru_cache.Get(1));
  EXPECT_EQ("three", lru_cache.Get(3));
}

TEST(LruCache, Emplace) {
  auto lru_cache = LruCache<int, std::string>{2};
  lru_cache.Emplace(1, "one");
  lru_cache.Emplace(2, "two");

  EXPECT_EQ("one", lru_cache.Get(1));
  EXPECT_EQ("two", lru_cache.Get(2));
}

TEST(LruCache, DoesNotCopyOnPush) {
  struct A {
    A() = default;
    ~A() = default;
    A(const A&) = delete;
    auto operator=(const A&) noexcept -> A& = delete;
    A(A&&) = default;
    auto operator=(A&&) noexcept -> A& = default;
  };
  static_assert(!std::is_copy_constructible_v<A> &&
                !std::is_copy_assignable_v<A>);

  auto lru_cache = LruCache<int, A>{2};
  lru_cache.Push(1, A{});
}
