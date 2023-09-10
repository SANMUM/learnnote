#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int maxArea(vector<int>& height) {
        int result = 0;
        int left = 0, right = height.size() - 1;
        while (left < right) {
            int ans = min(height[left], height[right]) * (right - left);
            result = max(result, ans);
            if (height[left] < height[right]) left++;
            else {
                right--;
            }
        }
        return result;
    }
};

int main() {
    vector<int> nums = {1,8,6,2,5,4,8,3,7};
    Solution ob;
    int ret = ob.maxArea(nums);
    cout << ret << endl;
}