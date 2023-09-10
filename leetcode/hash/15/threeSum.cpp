#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        int len = nums.size();
        vector<vector<int>> ret;
        int preid = -1;
        for(int i = 0; i < len; i++) {
            if(nums[i] > 0) {
                return ret;
            } 
            int left = i + 1;
            if( preid != -1 && nums[i] == nums[preid]) continue; // 保证起始点元素不同
            int right = len - 1;
            while (left < right) {
                int threeSum = nums[i] + nums[left] + nums[right];
                if(0 == threeSum) {
                    ret.push_back({nums[i],nums[left],nums[right]});
                    // int k = nums[left];
                    // while(k == nums[left] && left < right) left++;  // 去掉重复
                    // left++;
                    while(left<right && nums[right] == nums[right - 1]) right--;
                    while(left<right && nums[left] == nums[left+1]) left++;

                    left++;
                    right--;
                }
                else if(threeSum < 0) {
                    left++;
                }
                else
                {
                    right--;
                }
            }
            preid = i;
        }
        return ret;
    }
};

int main() {
    vector<int> nums = {-1,0,1,2,-1,-4};
    Solution ob;
    vector<vector<int>> ret = ob.threeSum(nums);
    int len = ret.size();
    for(int i = 0; i< len; i++) {
        for(auto it = ret[i].begin(); it != ret[i].end(); it++){
            cout<<*it<<"\t";
        }
        cout<<endl;
    }
}