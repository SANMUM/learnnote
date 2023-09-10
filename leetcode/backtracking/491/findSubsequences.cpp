#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    void backtrace(vector<int>& nums, int index) {
        if (path.size() >= 2) {
            ret.push_back(path);
            // return;
        }
        unordered_set<int> uset;
        for (int i = index; i < nums.size(); i++) {
            
            if ((!path.empty() && nums[i] < path.back()) || uset.find(nums[i]) != uset.end()) {
                continue;           
            }
            uset.insert(nums[i]);
            path.push_back(nums[i]);
            backtrace(nums, i+1);
            path.pop_back();
        }
    }
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        backtrace(nums,0);
        return ret;
    }
private:
vector<vector<int>> ret;
vector<int> path;
};

int main() {
    Solution ob;
    vector<int> nums = {4,6,7,7};
    // vector<int> nums = {4,4,3,2,1};
    vector<vector<int>> ret = ob.findSubsequences(nums);
    for (int i = 0; i < ret.size(); i++){
        for (auto it : ret[i]) {
            cout << it << "\t";
        }
        cout << endl;
    }
}
