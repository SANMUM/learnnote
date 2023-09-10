#include <bits/stdc++.h>
using namespace std;
class Solution{
public:
    void quicksort(vector<int>& nums, int left, int right){
        if (left+1 > right) return;
        int first = left, last = right -1;
        int key = nums[first];
        while(first < last) {
            while(first <  last && nums[last] >= key) last--;
            nums[first] = nums[last];
            while (first < last && nums[first] <= key) first++;
            nums[last] = nums[first];
        }
        nums[first] = key;
        quicksort(nums,left,first);
        quicksort(nums,first+1,right);
    }

   



};

int main() {
    vector<int> nums = {34,66,2,5,95,4,46,27};
    Solution ob;
    ob.quicksort(nums,0,nums.size());
    for (auto it: nums) {
        cout << it << "\t";
    }
    cout << endl;
}