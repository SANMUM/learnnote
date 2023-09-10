#include <bits/stdc++.h>
using namespace std; 
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int cover = 0;
        
        for (int i = 0; i <= cover; i++) {
            cover = max(i + nums[i],cover);
            if (cover >= nums.size()-1) return true;
        }
        return false;
    }
};

int main() {
    Solution ob;
    vector<int> nums = {3,0,8,2,0,0,1};
    bool ret = ob.canJump(nums);
    cout << boolalpha;
    cout << ret << endl;
}