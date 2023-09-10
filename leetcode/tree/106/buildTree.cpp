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
    TreeNode* traversal(vector<int>& inorder, vector<int>& postorder) {
        if (postorder.empty()) return nullptr;

        int val = postorder[postorder.size() - 1];
        TreeNode* root = new TreeNode(val);
        int index ;
        // 找到中序遍历的根节点位置
        for (index = 0; index < inorder.size(); index++) {
            if (inorder[index] == val) {
                break;
            }
        }
        // 分割中序数组
        vector<int> leftInorder(inorder.begin(),inorder.begin()+index);
        vector<int> rightInorder(inorder.begin() + index + 1, inorder.end());
        
        // 分割后序数组
        postorder.resize(postorder.size() - 1);
        vector<int> leftPostorder(postorder.begin(), postorder.begin() + leftInorder.size());
        vector<int> rightPostorder(postorder.begin() + leftInorder.size() , postorder.end());

        root->left = traversal(leftInorder, leftPostorder);
        root->right = traversal(rightInorder, rightPostorder);
        return root;
    }
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        if (inorder.empty() || postorder.empty()) return nullptr;
        return traversal(inorder, postorder);
    }
};