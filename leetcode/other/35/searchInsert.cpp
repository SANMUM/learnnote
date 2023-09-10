#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {

        int len = nums.size();
        int left = 0, right = len - 1;
        while (left <= right)
        {
            int mid = (left + right) / 2 ;
            if(nums[mid] == target){
                return mid;
            }
            else if(nums[mid]> target){
                right = mid - 1;
            }
            else{
                left = mid + 1;
            }
            // cout<<
        }
        return left;
    }
};

int main(){
    vector<int> nums = {1,3,5,6};
    int target = 2;
    Solution object;
    int ret = object.searchInsert(nums,target);
    cout<< ret<<endl;
}