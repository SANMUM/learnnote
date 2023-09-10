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
// 递归法
class Solution {
public:
    TreeNode* pre = nullptr;
    bool isValidBST(TreeNode* root) {
        
        if (root == nullptr)  return true;
        
        bool left = isValidBST(root->left);
        if (pre != nullptr && pre->val >= root->val) return false;
        pre = root;
        bool right = isValidBST(root->right);
        return left && right;
    }
};
// 迭代法
class Solution {
public:
   
    bool isValidBST(TreeNode* root) {
        
       stack<TreeNode*> st;
       TreeNode* cur = root;
       TreeNode* preNode = nullptr;
       
       while (cur != nullptr || !st.empty()) {
            if (cur != nullptr) {
                st.push(cur);
                cur = cur->left;
            }
            else {
                cur = st.top();
                st.pop();
                if (preNode != nullptr && preNode->val >= cur->val) {
                    return false;
                }
                preNode = cur;
                cur = cur->right;
            }
       }
       return true;
    }
};
