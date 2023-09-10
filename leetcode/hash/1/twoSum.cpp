#include<iostream>
#include<unordered_map>
#include<vector>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> umap;
        vector<int> result;
        for (int i = 0; i < nums.size(); i++) {
            if (umap.find(target-nums[i]) != umap.end()) {
                result.push_back(umap[target-nums[i]]);
                result.push_back(i);
                
                return result;
            }
            else {
                umap[nums[i]] = i;
            }
        }
        return {};
    }
};

int main() {
    vector<int> nums = {3,2,4};
    int target = 6;
    Solution ob;
    vector<int> ret = ob.twoSum(nums, target);
    for (auto it : ret) {
        cout << it << "\t";
    }
    cout << endl;
}