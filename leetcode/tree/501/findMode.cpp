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
    vector<int> findMode(TreeNode* root) {
        stack<TreeNode*> st;
        TreeNode* preNode = nullptr;
        TreeNode* cur = root;
        int count = 0;
        int maxCount = 0;
        vector<int> result;
        while (cur != nullptr || !st.empty()) {
            if ( cur != nullptr) {
                st.push(cur);
                cur = cur->left;
            }
            else {
                cur = st.top();
                st.pop();
                if (preNode == nullptr) {
                    count = 1;
                }
                else if (preNode->val ==  cur->val) {
                    count++;
                }
                else {
                    count = 1;
                }
                if (count == maxCount) {
                    result.push_back(cur->val);
                }
                if (count > maxCount) {
                    result.clear();
                    maxCount = count;
                    result.push_back(cur->val);
                }
                preNode = cur;
                cur = cur->right;
            }
        }
        return result;
    }
};