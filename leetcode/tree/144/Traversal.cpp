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

TreeNode* buildTree(vector<int>& nums) {
    TreeNode* root = new TreeNode(nums.front());
    queue<TreeNode*> que;
    que.push(root);
    int i = 1;
    while(!que.empty() && i < nums.size()) {
        TreeNode* temp = que.front();
        que.pop();
        if (i < nums.size()) {
            temp->left = new TreeNode(nums[i++]);
            que.push(temp->left);
        }
        if (i < nums.size()) {
            temp->right = new TreeNode(nums[i++]);
            que.push(temp->right);
        }
    }
    return root;
}

void PrintLevel(TreeNode* root) {
    if (root == nullptr) return ;
    queue<TreeNode*> que;
    vector<int> result;
    que.push(root);
    while (!que.empty()) {
        TreeNode* temp = que.front();
        que.pop();
        result.push_back(temp->val);
        if (temp->left) que.push(temp->left);
        if (temp->right) que.push(temp->right);
    }
    for (auto it : result) {
        cout << it << "\t";
    }
    cout << endl;
}

vector<int> preorderTraversal(TreeNode* root) {
    if (root == nullptr) return {};
    stack<TreeNode*> st;
    vector<int> result;
    st.push(root);
    while (!st.empty()) {
        TreeNode* temp = st.top();
        st.pop();
        result.push_back(temp->val);
        // cout << temp->val << "\t";
        if (temp->right) st.push(temp->right);
        if (temp->left) st.push(temp->left);
        // cout << endl;
    }
    return result;
}

vector<int> postorderTraversal(TreeNode* root) {
    if (root == nullptr) return {};
    stack<TreeNode*> st;
    vector<int> result;
    st.push(root);
    while (!st.empty()) {
        TreeNode* temp = st.top();
        st.pop();
        result.push_back(temp->val);
        // cout << temp->val << "\t";
        if (temp->left) st.push(temp->left);
        if (temp->right) st.push(temp->right);
        // cout << endl;
    }
    reverse(result.begin(), result.end());
    return result;
}

vector<int> inorderTraversal(TreeNode* root) {
    vector<int> result;
    if (root == nullptr) return {};
    stack<TreeNode*> st;
    TreeNode* cur = root;
    while (cur != nullptr || !st.empty()) {
        if (cur != nullptr) {
            st.push(cur);
            cur = cur->left;
        }
        else {
            cur = st.top();
            st.pop();
            result.push_back(cur->val);
            cur = cur->right;
        }
    }
    return result;
}
int main() {
    vector<int> nums = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    TreeNode *root = buildTree(nums);
    // PrintLevel(root);
    vector<int> result = preorderTraversal(root);
    for (auto it : result) {
        cout << it << "\t";
    }
    cout << endl;
}