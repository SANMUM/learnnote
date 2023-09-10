#include <bits/stdc++.h>
using namespace std;
class Solution{
public:
    void selectsort(vector<int>& nums){
        int len = nums.size();
        if (len <=1) return;
        for (int i = 0; i < len - 1; i++) {
            int mid = i;
            for (int j = i+1; j < len; j++) {
                if (nums[j] < nums[mid]) {
                    mid = j;
                }
            }
             swap(nums[i],nums[mid]);
        }
    }

   



};

int main() {
    vector<int> nums = {34,66,2,5,95,4,46,27};
    Solution ob;
    ob.selectsort(nums);
    for (auto it: nums) {
        cout << it << "\t";
    }
    cout << endl;
}