#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> ret;
        int len = nums.size();
        for(int k = 0; k < len; k++) {
            if(nums[k] > target && nums[k]>=0) break;
            if((k > 0) && (nums[k] == nums[k - 1])) continue;
            for(int i = k+1; i < len; i++) {
                if((nums[k] + nums[i] > target) && (nums[k] + nums[i] >= 0)) break;
                if( (i>k+1) && (nums[i] == nums[i-1])) continue;
                int left = i+1;
                int right = len - 1;
                while (left < right) {
                    long foureSum = (long) nums[k] + nums[i] + nums[left] + nums[right];
                    if(foureSum == target) {
                        ret.push_back({nums[k],nums[i],nums[left], nums[right]});
                        while(left < right && nums[left] == nums[left+1]) left++;
                        while(left <right && nums[right] == nums[right-1]) right--;
                        left++;
                        right--; 
                    }
                    else if(foureSum < target){
                        left++;
                    }
                    else
                    {
                        right--;
                    }
                }
            } 
        }
        return ret;
    }
};
int main() {
    vector<int> nums = {1,0,-1,0,-2,2};
    int target = 0;
    Solution ob;
    vector<vector<int>> ret = ob.fourSum(nums,target);
    int len = ret.size();
    for(int i = 0; i< len; i++) {
        for(auto it = ret[i].begin(); it != ret[i].end(); it++){
            cout<<*it<<"\t";
        }
        cout<<endl;
    }
}