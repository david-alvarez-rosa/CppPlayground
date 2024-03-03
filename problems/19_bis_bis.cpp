#include <bits/stdc++.h>
#include <gmock/gmock.h>
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
  ListNode* removeNthFromEnd(ListNode* head, int n) {
    auto tmp = head;
    int height{0};
    while (tmp) {
      height++;
      tmp = tmp->next;
    }

    if (n == height) return head->next;

    tmp = head;
    for (int i{0}; i < height - n - 1; i++) tmp = tmp->next;

    tmp->next = tmp->next->next;
    return head;
  }
};

MATCHER_P(IsEqualLinkedList, const_lhs, "Equal linked list") {
  ListNode* rhs = arg;
  ListNode* lhs = const_lhs;

  while (rhs) {
    if (!lhs) return false;
    if (lhs->val != rhs->val) return false;
    rhs = rhs->next;
    lhs = lhs->next;
  }

  if (lhs) return false;

  return true;
}

TEST(SolutionTest, Test1) {
  Solution solution;
  auto head = new ListNode(
      1, new ListNode(2, new ListNode(3, new ListNode(4, new ListNode(5)))));
  EXPECT_THAT(solution.removeNthFromEnd(head, 2),
              IsEqualLinkedList(new ListNode(
                  1, new ListNode(2, new ListNode(3, new ListNode(5))))));
}

TEST(SolutionTest, Test2) {
  Solution solution;
  auto head = new ListNode(1);
  EXPECT_THAT(solution.removeNthFromEnd(head, 1), IsEqualLinkedList(nullptr));
}

TEST(SolutionTest, Test3) {
  Solution solution;
  auto head = new ListNode(1, new ListNode(2));
  EXPECT_THAT(solution.removeNthFromEnd(head, 1),
              IsEqualLinkedList(new ListNode(1)));
}
