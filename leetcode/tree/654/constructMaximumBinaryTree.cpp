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
    TreeNode* Traversal(vector<int> nums) {
        if (nums.empty()) return nullptr;
        auto it = max_element(nums.begin(), nums.end());
        TreeNode* root = new TreeNode(*it);
        vector<int> leftVec(nums.begin(),it);
        vector<int> rightVec(it+1, nums.end());
        root->left = Traversal(leftVec);
        root->right = Traversal(rightVec);
        return root;
    }
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        
        return Traversal(nums);
    }

};

int main() {
   
}