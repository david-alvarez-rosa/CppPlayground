#include <bits/stdc++.h>
#include <gtest/gtest.h>

using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val{0}, left{nullptr}, right{nullptr} {}
  TreeNode(int x) : val{x}, left{nullptr}, right{nullptr} {}
  TreeNode(int x, TreeNode* left, TreeNode* right)
      : val{x}, left{left}, right{right} {}
};

class Solution {
 public:
  bool isSameTree(TreeNode* p, TreeNode* q) {
    if (p == nullptr && q == nullptr) return true;
    if (p == nullptr || q == nullptr) return false;
    return p->val == q->val && isSameTree(p->left, q->left) &&
           isSameTree(p->right, q->right);
  }
};

TEST(SolutionTest, Test1) {
  Solution solution;
  TreeNode* p = new TreeNode(1, new TreeNode(2), new TreeNode(3));
  TreeNode* q = new TreeNode(1, new TreeNode(2), new TreeNode(3));
  EXPECT_TRUE(solution.isSameTree(p, q));
}

TEST(SolutionTest, Test2) {
  Solution solution;
  TreeNode* p = new TreeNode(1, new TreeNode(2), nullptr);
  TreeNode* q = new TreeNode(1, nullptr, new TreeNode(2));
  EXPECT_FALSE(solution.isSameTree(p, q));
}

TEST(SolutionTest, Test3) {
  Solution solution;
  TreeNode* p = new TreeNode(1, new TreeNode(2), new TreeNode(1));
  TreeNode* q = new TreeNode(1, new TreeNode(1), new TreeNode(2));
  EXPECT_FALSE(solution.isSameTree(p, q));
}
