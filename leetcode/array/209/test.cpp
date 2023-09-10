#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int i = 0;
        int sum = 0;
        int ret = INT32_MAX;
        for (int j = 0; j < nums.size(); j++) {
            sum += nums[j];
            while (sum >= target) {
                ret = min(ret, j - i + 1);
                sum -= nums[i++];
            }
        }
        return ret == INT32_MAX ? 0: ret;
    }
};

int main() {
    Solution ob;
    vector<int> nums = {2,3,1,2,4,3};
    int ret = ob.minSubArrayLen(7,nums);
    cout << ret << endl;
}