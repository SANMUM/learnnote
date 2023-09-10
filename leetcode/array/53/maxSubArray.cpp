#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int len = nums.size();
        int ret = nums[0];
        int sum = 0;
        for(int i = 0; i < len; i++){
            int value = nums[i];
            if(sum>0){
                sum += value;
            }
            else{
                sum = value;
            }
            ret = max(ret,sum);

        }
        return ret;

    }
};

int main(){
    Solution ob;
    vector<int> nums = {-2,1,-3,4,-1,2, 1,-5,4};
    int res = ob.maxSubArray(nums);
    cout<< res<<endl;
}