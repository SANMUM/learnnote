#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int sum = 0;
        int ret = INT32_MIN;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
            ret = max(ret,sum);
            // if (sum > ret) {
            //     ret = sum;
            // }
            if (sum <= 0) {
                sum = 0;
            }
            
            
        }
        return ret;
    }
};

int main() {
    Solution ob;
    // vector<int> nums = {-2,1,-3,4,-1,2,1,-5,4};
    vector<int> nums = {-1};
    int ret = ob.maxSubArray(nums);
    cout << ret << endl;
}