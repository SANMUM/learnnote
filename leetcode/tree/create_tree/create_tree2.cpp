#include<iostream>
#include<vector>
#include<queue>
using namespace std;

struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int value): val(value), left(nullptr), right(nullptr) {}
};

class Soulution {

public:
    TreeNode* constructTree(vector<int>& nums) {
        vector<TreeNode*> vecTree(nums.size(), nullptr);
        TreeNode* root = nullptr;
        for (int i = 0; i < nums.size(); i++) {
            TreeNode* node = nullptr;
            if (nums[i] != -1) {
                node = new TreeNode(nums[i]);
            }
            vecTree[i] = node;
            if (i == 0) {
                root = node;
            }
        }
        for (int i = 0; i*2+1 < nums.size(); i++) {
            if (vecTree[i] != nullptr) {
                vecTree[i]->left = vecTree[i*2+1];
                if (i * 2 + 2 < vecTree.size()) {
                    vecTree[i]->right = vecTree[i*2+2];
                }
            }
        }
        return root;
    }
    void levelPrint(TreeNode* root) {
        queue<TreeNode*> queTree;
        vector<vector<int>> result;
        if (root) {
            queTree.push(root);
        }
        while (!queTree.empty()) {
            vector<int> vec;
            int size = queTree.size();
            for (int i = 0; i < size; i++) {
                TreeNode* node = queTree.front();
                queTree.pop();
                if (node) {
                    vec.push_back(node->val);
                    queTree.push(node->left);
                    queTree.push(node->right);
                }
                else {
                    vec.push_back(-1);
                }
            }
            result.push_back(vec);
        }
        for (int i = 0; i < result.size(); i++) {
            for (auto it : result[i]) {
                cout << it << "\t";
            }
            cout << endl;
        }

    }
};

int main() {
    Soulution ob;
    vector<int> nums = {4,1,6,0,2,5,7,-1,-1,-1,3,-1,-1,-1,8};
    TreeNode* root =  ob.constructTree(nums);
    ob.levelPrint(root);
}