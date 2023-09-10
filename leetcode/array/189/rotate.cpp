#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    void reverse(vector<int>& nums, int start, int end) {
        while (start < end)
        {
            /* code */
            swap(nums[start], nums[end]);
            start++;
            end--;
        }
        
    }
    void rotate(vector<int>& nums, int k) {
        int len = nums.size();
        k = k % len;
        reverse(nums, 0, len-1);
        reverse(nums, 0, k - 1);
        reverse(nums, k, len - 1);
        
    }
};

int main(int argc, char const *argv[])
{
    vector<int> nums = {1,2,3,4,5,6,7};
    int k = 3;
    Solution ob;
    ob.rotate(nums, k);
    for (auto it : nums) {
        cout << it << " ";
    }     
    cout << endl;
    return 0;
}
