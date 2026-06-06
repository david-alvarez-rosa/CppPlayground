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
    unordered_set<ListNode*> visited;
    while (head) {
      if (visited.contains(head)) return true;
      visited.insert(head);
      head = head->next;
    }
    return false;
  }
};
