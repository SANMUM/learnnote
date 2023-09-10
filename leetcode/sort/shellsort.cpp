#include <bits/stdc++.h>
using namespace std;
class Solution{
public:
    void shellsort(vector<int>& nums){
     for (int gap = nums.size()/2; gap > 0; gap /= 2) {
        for (int i = gap; i < nums.size(); i++) {
            for (int j = i; j - gap >=0 && nums[j-gap] > nums[j];j -=gap) {
                swap(nums[j-gap], nums[j]);
            }
        }
     }   
    }
};

int main() {
    vector<int> nums = {34,66,2,5,95,4,46,27};
    Solution ob;
    ob.shellsort(nums);
    for (auto it: nums) {
        cout << it << "\t";
    }
    cout << endl;
}