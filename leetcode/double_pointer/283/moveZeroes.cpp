#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int n = nums.size();
        int left = 0, right = 0;
        while (right < n) {
            if (nums[right] ) {
                swap(nums[left], nums[right]);
                
                left++;
            }
            right++;
        }
        // for (auto it : nums) {
        //     cout << it << endl;
        // }
    }
};

int main() {
    vector<int> nums = {0,1,0,3,12};
    Solution ob;
    ob.moveZeroes(nums);
}