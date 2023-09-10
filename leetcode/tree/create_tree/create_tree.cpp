#include <iostream>
#include <vector>
#include <queue>
using namespace std;
 
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
 
TreeNode* buildTree(vector<int>& nums)
{
	if (nums.empty()) return nullptr;
    TreeNode *root = new TreeNode(nums.front());
    // vector<TreeNode*> q = {root};
    queue<TreeNode*> q;
    q.push(root);
    
    int i = 1;
    while(!q.empty() && i < nums.size())
    {
        TreeNode *cur = q.front();
        // q.assign(q.begin() + 1, q.end());
        q.pop();
        if(i < nums.size())
        {
            cur->left = new TreeNode(nums[i++]);
            // q.push_back(cur->left);
            q.push(cur->left);
        }
        if(i < nums.size())
        {
            cur->right = new TreeNode(nums[i++]);
            // q.push_back(cur->right);
            q.push(cur->right);
        }
    }
    return root;
}


void levelOrderPrint(TreeNode* root)
{
    if(!root) return;
    vector<TreeNode*> q = {root};
    while(!q.empty())
    {
        int size = q.size();
        for(int i = 0; i < size; i++)
        {
            TreeNode *cur = q.front();
            q.assign(q.begin() + 1, q.end());
            cout << cur->val << " ";
            if(cur->left)
                q.push_back(cur->left);
            if(cur->right)
                q.push_back(cur->right);
        }
        cout << endl;
    }
}

int main()
{
    vector<int> nums = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    TreeNode *root = buildTree(nums);
    levelOrderPrint(root);
    // vector<int> nums = {1,2,3};
    // nums.assign(nums.begin()+1, nums.end());
    // for (auto it :nums) {
    //     cout << it << "\t";
    // }
 
    return 0;
}