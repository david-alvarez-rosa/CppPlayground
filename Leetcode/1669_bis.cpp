#include <bits/stdc++.h>

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
  ListNode* mergeInBetween(ListNode* list1, int a, int b, ListNode* list2) {
    auto ath_node{list1};
    int c = b - a + 1;
    while (--a) ath_node = ath_node->next;
    auto bth_node{ath_node};
    while (c--) bth_node = bth_node->next;
    ath_node->next = list2;

    auto last{list2};
    while (last->next) last = last->next;
    last->next = bth_node->next;
    return list1;
  }
};
