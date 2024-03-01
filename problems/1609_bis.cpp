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
  bool isEvenOddTree(TreeNode* root) {
    if (root == nullptr) return true;

    queue<pair<TreeNode*, TreeNode*>> q;
    q.push({root, nullptr});

    while (!q.empty()) {
      auto [node, parent] = q.front();
      q.pop();
    }

    return true;
  }
};

TEST(SolutionTest, Test1) {
  Solution solution;
  TreeNode* root = new TreeNode(
      1,
      new TreeNode(10, new TreeNode(3, new TreeNode(12), new TreeNode(8)),
                   nullptr),
      new TreeNode(4, new TreeNode(7, new TreeNode(6), nullptr),
                   new TreeNode(9, nullptr, new TreeNode(2))));
  EXPECT_TRUE(solution.isEvenOddTree(root));
}

TEST(SolutionTest, Test2) {
  Solution solution;
  TreeNode* root =
      new TreeNode(5, new TreeNode(4, new TreeNode(3), new TreeNode(3)),
                   new TreeNode(2, new TreeNode(7), nullptr));
  EXPECT_FALSE(solution.isEvenOddTree(root));
}

TEST(SolutionTest, Test3) {
  Solution solution;
  TreeNode* root =
      new TreeNode(5, new TreeNode(9, new TreeNode(3), new TreeNode(5)),
                   new TreeNode(1, new TreeNode(7), nullptr));
  EXPECT_FALSE(solution.isEvenOddTree(root));
}
