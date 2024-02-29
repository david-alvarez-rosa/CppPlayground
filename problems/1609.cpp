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
    queue<pair<TreeNode*, int>> q;
    q.push({root, 0});
    TreeNode* prev_node = nullptr;
    auto prev_height = -1;
    while (!q.empty()) {
      auto [node, height] = q.front();
      q.pop();

      if (height % 2 == 0) {
        if (node->val % 2 == 0) return false;
        if (prev_height == height && prev_node->val >= node->val) return false;
      }

      if (height % 2 == 1) {
        if (node->val % 2 == 1) return false;
        if (prev_height == height && prev_node->val <= node->val) return false;
      }

      if (node->left) q.push({node->left, height + 1});
      if (node->right) q.push({node->right, height + 1});
      prev_node = node;
      prev_height = height;
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
