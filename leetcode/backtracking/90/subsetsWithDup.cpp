#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
void backtracking(vector<int>& nums, int index) {
        ret.push_back(path);

        for (int i = index; i < nums.size(); i++) {
            if (i>index && nums[i] == nums[i-1]) {
                continue;
            }
            if (index >= nums.size()) {
                return;
            }
            path.push_back(nums[i]);
            backtracking(nums, i+1);
            path.pop_back();
        }
    }
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        backtracking(nums, 0);
        return ret;
    }
private:
vector<vector<int>> ret;
vector<int> path;
};


int main() {
    Solution ob;
    vector<int> nums = {1,2,2};
    vector<vector<int>> ret = ob.subsetsWithDup(nums);
    for (int i = 0; i < ret.size(); i++){
        for (auto it : ret[i]) {
            cout << it << "\t";
        }
        cout << endl;
    }
}