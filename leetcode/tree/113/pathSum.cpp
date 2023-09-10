#include <bits/stdc++.h>
using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    void backtrace(TreeNode* node, int count) {
        if (node->left == nullptr && node->right == nullptr && count == 0) {
            result.push_back(path);
            return;
        }
        if (node->left == nullptr && node->right == nullptr) return;
        if (node->left) {
            count -= node->left->val;
            path.push_back(node->left->val);
            backtrace(node->left,count);
            count += node->left->val;
            path.pop_back();
        }
        if (node->right) {
            count -= node->right->val;
            path.push_back(node->right->val);
            backtrace(node->right, count);
            count += node->right->val;
            path.pop_back();
        }
       
    }
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        if (root == nullptr) return {};
        path.push_back(root->val);
        backtrace(root,targetSum - root->val);
        return result;
    }
private:
    vector<int> path;
    vector<vector<int>> result;
};