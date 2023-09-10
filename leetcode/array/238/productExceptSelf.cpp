#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int len = nums.size();
        vector<int> result(len, 1);
        int temp = 1;
        for (int i = 1; i < len; i++) {
            result[i] = result[i-1] *  nums[i-1];
        }
        for (auto it : result) {
            cout << it  << " ";
        }
        cout << endl;
        for (int i = len - 2; i >=0; i--) {
            temp *= nums[i+1];
            result[i] *= temp;
        }
        return result;
    }
};

int main() {
    vector<int> nums = {1,2,3,4};
    Solution ob;
    vector<int> ret = ob.productExceptSelf(nums);
    for (auto it : ret) {
        cout << it  << " ";
    }
    cout << endl;
}