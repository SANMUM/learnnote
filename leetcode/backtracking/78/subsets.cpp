#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    void backtracking(vector<int>& nums, int index) {
        ret.push_back(path);

        for (int i = index; i < nums.size(); i++) {
            if (index >= nums.size()) {
                return;
            }
            path.push_back(nums[i]);
            backtracking(nums, i+1);
            path.pop_back();
        }
    }
    vector<vector<int>> subsets(vector<int>& nums) {
        backtracking(nums, 0);
        return ret;

    }
private:
vector<vector<int>> ret;
vector<int> path;
};

int main() {
    Solution ob;
    vector<int> nums = {1,2,3};
    vector<vector<int>> ret = ob.subsets(nums);
    for (int i = 0; i < ret.size(); i++){
        for (auto it : ret[i]) {
            cout << it << "\t";
        }
        cout << endl;
    }
}