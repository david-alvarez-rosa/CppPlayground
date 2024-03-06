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
  bool hasCycle(ListNode* head) {
    auto slow{head}, fast{head};
    while (fast && fast->next) {
      slow = slow->next;
      fast = fast->next->next;
      if (slow == fast) return true;
    }
    return false;
  }
};
