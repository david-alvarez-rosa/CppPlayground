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
  int diameterOfBinaryTree(TreeNode* root) {
    if (!root) return 0;
    auto left_diameter = diameterOfBinaryTree(root->left);
    auto right_diameter = diameterOfBinaryTree(root->right);
    auto root_diameter = height(root->left) + height(root->right);
    return max(left_diameter, max(right_diameter, root_diameter));
  }

 private:
  int height(TreeNode* root) {
    if (!root) return 0;
    return 1 + max(height(root->left), height(root->right));
  }
};

TEST(SolutionTest, Test1) {
  Solution solution;
  TreeNode* root = new TreeNode(
      1, new TreeNode(2, new TreeNode(4), new TreeNode(5)), new TreeNode(3));
  EXPECT_EQ(3, solution.diameterOfBinaryTree(root));
}

TEST(SolutionTest, Test2) {
  Solution solution;
  TreeNode* root = new TreeNode(1, new TreeNode(2), nullptr);
  EXPECT_EQ(1, solution.diameterOfBinaryTree(root));
}
