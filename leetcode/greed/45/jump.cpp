#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int jump(vector<int>& nums) {
        int curDistance = 0;
        int nextDistance = 0;
        int res = 0;
        int len = nums.size();
        for (int i = 0; i < len-1; i++) {
            nextDistance = max(i + nums[i], nextDistance);
            if (i == curDistance) {
                curDistance = nextDistance;
                res++;
            }
        }
        return res;
    }
};
int main() {
    vector<int> nums = {2,3,0,1,4};
    Solution ob;
    int ret = ob.jump(nums);
    cout << ret << endl;
}