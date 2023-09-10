#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int wiggleMaxLength(vector<int>& nums) {

        int len = nums.size();
        int ret = 1;
        int prediff = 0;
        int nextdiff = 0;
        
        for (int i = 0; i < len - 1; i++) {
            nextdiff = nums[i+1] - nums[i];
            if ((prediff>=0 && nextdiff < 0) || (prediff<=0 && nextdiff > 0)) {
                ret++;
                prediff = nextdiff;
            }
        }
        return ret;
    }
};
int main() {
    Solution ob;
    // vector<int> nums = {1, 7, 4, 9, 2, 5};
    vector<int> nums = {1,17,5,10,13,15,10,5,16,8};
    // vector<int> nums = {1,2,3,4,5,6,7,8,9};
    int ret = ob.wiggleMaxLength(nums);
    cout << ret << endl;
}