#include <gtest/gtest.h>

#include <stack>
#include <string>

class Solution {
 public:
  [[nodiscard]] static auto isValid(std::string input) noexcept -> bool {
    auto st = std::stack<char>{};

    for (auto c : input) {
      if (c == '(' || c == '[' || c == '{') {
        st.push(c);
      } else {
        if (st.empty()) {
          return false;
        }
        auto top = st.top();
        st.pop();
        if ((c == ')' && top != '(') || (c == ']' && top != '[') ||
            (c == '}' && top != '{')) {
          return false;
        };
      }
    }

    return st.empty();
  }
};

TEST(Solution, Test1) { EXPECT_TRUE(Solution::isValid("()")); }
TEST(Solution, Test2) { EXPECT_TRUE(Solution::isValid("()[]{}")); }
TEST(Solution, Test3) { EXPECT_FALSE(Solution::isValid("(]")); }
TEST(Solution, Test4) { EXPECT_TRUE(Solution::isValid("([])")); }
TEST(Solution, Test5) { EXPECT_FALSE(Solution::isValid("([)]")); }
