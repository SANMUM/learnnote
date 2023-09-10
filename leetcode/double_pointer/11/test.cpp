#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        int result = 0;
        int left = 0, right = height.size() - 1;
        while (left < right) {
            int ans =  min(height[left], height[right]) * (right - left);
            result = max(ans, result);
            if (height[left] < height[right]) {
                left++;
            }
            else {
                right--;
            }
        }
        return result;
    }
};
int main() {
    Solution ob;
    vector<int> height = {1,8,6,2,5,4,8,3,7};
    int ret = ob.maxArea(height);
    cout << ret << endl;
}