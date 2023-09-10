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
    TreeNode* invertTree(TreeNode* root) {
        if (root == nullptr) return nullptr;
        queue<TreeNode*> que;
        que.push(root);
        while (!que.empty()) {
            TreeNode* temp = que.front();
            que.pop();
            swap(temp->left, temp->right);
            if (temp->left) que.push(temp->left);
            if (temp->right) que.push(temp->right);
        }
        return root;
    }
    
};