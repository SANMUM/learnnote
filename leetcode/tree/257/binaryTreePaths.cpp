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
    void backtracing(TreeNode* cur) {
        path.push_back(cur->val);
        if (cur->left == nullptr && cur->right==nullptr) {
            string s;
            for (int i = 0; i < path.size() - 1; i++ ) {
                s += to_string(path[i]);
                s += "->";
            }
            s += to_string(path[path.size() - 1]);
            ret.push_back(s);
            return;
        }
        if (cur->left) {
            backtracing(cur->left);
            path.pop_back();
        }

        if (cur->right) {
            backtracing(cur->right);
            path.pop_back();
        }
    }
    vector<string> binaryTreePaths(TreeNode* root) {
        if (root == nullptr) return {};
        backtracing(root);
        return ret;
    }
private:
    vector<string> ret;
    vector<int> path;
};

