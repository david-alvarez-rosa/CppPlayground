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
  int findBottomLeftValue(TreeNode* root) {
    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
      root = q.front();
      q.pop();
      if (root->right) q.push(root->right);
      if (root->left) q.push(root->left);
    }

    return root->val;
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
