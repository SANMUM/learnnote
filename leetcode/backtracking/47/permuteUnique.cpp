#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void backtracking(vector<int>& nums, vector<bool>& used) {
        if (path.size() == nums.size()) {
            ret.push_back(path);
            return;
        }
        unordered_set<int> uset;
        for (int i = 0; i < nums.size(); i++) {
            if ((i>0 && nums[i] == nums[i-1]) && used[i-1] == false) {
                continue;
            }
            if (used[i] == false) {
                used[i] = true;
                path.push_back(nums[i]);
                backtracking(nums,used);
                used[i] = false;
                path.pop_back();
            }
           
        }
    }
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        vector<bool> used(nums.size(), false);
        backtracking(nums,used);
        return ret;
    }
private:
    vector<int> path;
    vector<vector<int>> ret;
};

int main() {
    Solution ob;
    // vector<int> nums = {1,2,3};
    vector<int> nums = {1,1,2};
    vector<vector<int>> ret = ob.permuteUnique(nums);
    for (int i = 0; i < ret.size(); i++) {
        for (auto it : ret[i]) {
            cout << it << "\t";
        }
        cout << endl;
    }
}