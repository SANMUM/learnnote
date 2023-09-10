#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int largestSumAfterKNegations(vector<int>& nums, int k) {
        sort(nums.begin(),nums.end(), [](int a, int b){
            return abs(a) > abs(b);
        });
        int len = nums.size();
        int ret = 0;
        for (int i = 0; i < len; i++) {
            if (nums[i] < 0 && k > 0) {
                nums[i] *= -1;
                k--;
            }
        }
        if ( k%2 == 1) nums[len-1] *= -1;
        for (auto it : nums) {
            ret += it;
        }  
        return ret;
    }
};
int main() {
    vector<int> nums = {2,-3,-1,5,-4};
    int k = 2;
    Solution ob;
    int result = ob.largestSumAfterKNegations(nums,k);
    cout << result << endl;
}