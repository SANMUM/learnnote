#include <bits/stdc++.h>
using namespace std;
class Solution{
public:
    void insertsort(vector<int>& nums){
        int len = nums.size();
        if (len <=1) return;
        for (int i = 0; i < len; i++) {
            for (int j = i; j > 0 && nums[j] < nums[j-1];j--) {
                swap(nums[j],nums[j-1]);
            }
        }
    }

   



};

int main() {
    vector<int> nums = {34,66,2,5,95,4,46,27};
    Solution ob;
    ob.insertsort(nums);
    for (auto it: nums) {
        cout << it << "\t";
    }
    cout << endl;
}