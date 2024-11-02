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
  int findBottomLeftValue(TreeNode* root) { return trackedHeight(root).second; }

 private:
  pair<int, int> trackedHeight(TreeNode* root) {  // (height, value)
    pair<int, int> left = {0, 0};
    if (root->left) left = trackedHeight(root->left);

    pair<int, int> right = {0, 0};
    if (root->right) right = trackedHeight(root->right);

    if (left.first == 0 && right.first == 0) return {1, root->val};

    if (right.first > left.first) return {1 + right.first, right.second};
    return {1 + left.first, left.second};
  }
};

TEST(SolutionTest, Test1) {
  Solution solution;
  TreeNode* root = new TreeNode(2, new TreeNode(1), new TreeNode(3));
  EXPECT_EQ(1, solution.findBottomLeftValue(root));
}

TEST(SolutionTest, Test2) {
  Solution solution;
  TreeNode* root =
      new TreeNode(7, new TreeNode(2, new TreeNode(4), nullptr),
                   new TreeNode(3, new TreeNode(5, new TreeNode(7), nullptr),
                                new TreeNode(6)));
  EXPECT_EQ(7, solution.findBottomLeftValue(root));
}
