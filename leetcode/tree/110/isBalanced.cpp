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
    int getDepth(TreeNode* root) {
        if (root == nullptr) return 0;
        int ldepth = getDepth(root->left);
        if (ldepth == -1) return -1;
        int rdepth = getDepth(root->right);
        if (rdepth == -1) return -1;
        return abs(ldepth - rdepth) > 1 ? -1 : (1+ max(ldepth, rdepth));
    }
    bool isBalanced(TreeNode* root) { 
        if (root == nullptr) return true;
        return getDepth(root) == -1 ? false : true;

    }
};