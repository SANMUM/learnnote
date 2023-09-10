#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int left = 0, right = nums.size() - 1;
        vector<int> result(nums.size(), 0);
        int k = right;
        while (left <= right) {
            if (nums[left] * nums[left] < nums[right]*nums[right]) {
                result[k--] = nums[right]* nums[right];
                right--;
            }
            else {
                result[k--] = nums[left] * nums[left];
                left++;
            }
        }
        return result;
    }
};

int main() {
    vector<int> nums = {-4,-1,0,3,10};
    Solution ob;
    vector<int> ret = ob.sortedSquares(nums);
    for (auto it : ret) {
        cout << it << "\t";
    }
    cout << endl;
}