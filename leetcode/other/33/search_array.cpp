#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    
    int search(vector<int>& nums, int target) {
        int n = nums.size();
        if(!n) return -1;
        if(n == 1){
            return target == nums[0] ? 0: -1;
        }
        int left = 0, right = n - 1;     
        while(left <= right){
            int mid = (left + right) / 2;
            if(nums[mid] == target) return mid;
            if( nums[0] <= nums[mid] ){
                if(nums[0] <= target && target < nums[mid]){
                    
                    right = mid - 1;
                    
                }
                else{
                    left = mid + 1;
                }
            }
            else{
                if(target > nums[mid] && target <= nums[n-1]){
                    left = mid + 1;
                    
                }
                else{
                    right = mid - 1;
                }
            }
        }
        return -1;
    }
};


int main(){
    vector<int> nums = {4,5,6,7,8,0,1,2};
    int target = 8;
    Solution main;
    int ret = main.search(nums,target);
    cout<<ret<<endl;
}