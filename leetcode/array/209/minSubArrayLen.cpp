#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int len = nums.size();
        int i = 0;
        int sum = 0;
        int ret = INT32_MAX;
        for (int j = 0; j < len; j++) {
            sum += nums[j];
            while (sum >=target){
                ret = min(j-i+1,ret);
                sum -= nums[i++];
            } 
        }
        return ret == INT32_MAX ? 0 : ret;
    }
};
int main(){
    vector<int> nums = {1,4,4};
    int target = 4;
    Solution ob;
    int ret = ob.minSubArrayLen(target,nums);
    std::cout << ret << endl;
}
