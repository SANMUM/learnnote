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
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (root == nullptr) return nullptr;
        if (root->val == key) {
            if (root->left == nullptr && root->right == nullptr) {
                return nullptr;
            }
            else if (root->left != nullptr && root->right == nullptr) {
                return root->left;
            }
            else if (root->left == nullptr && root->right != nullptr) {
                return root->right;
            }
            else {
                TreeNode* curnode = root->right;
                while (curnode->left != nullptr) {
                    curnode = curnode->left;
                }
                curnode->left = root->left;
                // root->right = 
                TreeNode* temp = root;
                root = root->right;
                return root;
            }
        }
        else if (root->val > key) {
            root->left = deleteNode(root->left, key);
        }
        else {
            root->right = deleteNode(root->right, key);
        } 
        return root;
    }
};