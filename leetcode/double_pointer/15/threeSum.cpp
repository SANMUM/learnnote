#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> reuslt;
        sort(nums.begin(), nums.end());
        int len = nums.size();
        
        for (int i = 0; i < len; i++) {
            int left = i+1, right = len - 1;
            if (nums[i] > 0) break;
            if (i>0 && nums[i] == nums[i-1]) continue;
            while (left < right) {
                int ans = nums[i] + nums[left] + nums[right];
                if (ans == 0) {
                    reuslt.push_back({ nums[i], nums[left], nums[right]});
                    while (left < right && nums[left] == nums[left+1]) left++;
                    while (left < right && nums[right] == nums[right-1]) right--;
                    right--;
                    left++;
                }
                else if (ans < 0)  {
                    left++;
                }
                else {
                    right--;
                }
            }
        }
        return reuslt;
    }
};

int main() {
    vector<int> nums = {-1,0,1,2,-1,-4};
    Solution ob;
    vector<vector<int>> ret = ob.threeSum(nums);
    for (int i = 0; i < ret.size(); i++) {
        for (auto it : ret[i]) {
            cout << it << "\t";
        }
        cout << endl;
    }
}