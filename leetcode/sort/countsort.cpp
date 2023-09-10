#include <bits/stdc++.h>
using namespace std;
class Solution{
public:
    void countsort(vector<int>& nums) {
        int len = nums.size();
        int maxV = nums[0];
        for (int i = 0; i < len; i++) {
            maxV = max(maxV, nums[i]);
        }
        // cout << maxV;
        vector<int> cvec(maxV,0);
        for (int i = 0; i < len; i++) {
            cvec[nums[i]]++;
        }
        for (int i = 1; i <= maxV; i++) {
            cvec[i]+=cvec[i-1];
        }
        vector<int> rvec(maxV, 0);
        for (int i = len - 1; i>=0; i--) {
            int index = cvec[nums[i]] -1;
            rvec[index] = nums[i];
            cvec[nums[i]]--;
        }
        for (int i = 0; i < len; i++) {
            nums[i] = rvec[i];
        }

        
    }
};

int main() {
    vector<int> nums = {2,4,1,2,5,3,4,8,7};
    // vector<float> nums = {0.78,0.17,0.39,0.26,0.72,0.94,0.21,0.12,0.23,0.68};
    Solution ob;
    // ob.heap_sort(nums,sizeof(nums)/sizeof(int));
    ob.countsort(nums);
    for (auto it: nums) {
        cout << it << "\t";
    }
    cout << endl;
}