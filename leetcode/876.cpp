#include <bits/stdc++.h>
#include <gtest/gtest.h>

using namespace std;

struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val{0}, next{nullptr} {}
  ListNode(int x) : val{x}, next{nullptr} {}
  ListNode(int x, ListNode* next) : val{x}, next{next} {}
};

class Solution {
 public:
  ListNode* middleNode(ListNode* head) {
    auto slow{head}, fast{head};
    while (fast && fast->next) {
      slow = slow->next;
      fast = fast->next->next;
    }
    return slow;
  }
};

TEST(SolutionTest, Test1) {
  Solution solution;
  auto middle = new ListNode(3, new ListNode(4, new ListNode(5)));
  auto head = new ListNode(1, new ListNode(2, middle));
  EXPECT_EQ(middle, solution.middleNode(head));
}

TEST(SolutionTest, Test2) {
  Solution solution;
  auto middle = new ListNode(4, new ListNode(5, new ListNode(6)));
  auto head = new ListNode(1, new ListNode(2, new ListNode(3, middle)));
  EXPECT_EQ(middle, solution.middleNode(head));
}
