#include <bits/stdc++.h>
using namespace std;
class Solution{
public:
    void mergetCount(vector<int>& nums, int left, int mid, int right) {
        vector<int> temp(left+mid+right,0);
        int i = left;
        int j = mid + 1;
        int k = 0;
        while(i <= mid && j <= right) {
            if (nums[i] < nums[j]) {
                temp[k++] = nums[i++];
            }
            else {
                temp[k++] = nums[j++];
            }
        }
        while ( i <= mid) {
            temp[k++] = nums[i++];
        }
        while (j <= right) {
            temp[k++] = nums[j++];
        }
        for (int p = 0; p < k; p++) {
            nums[left+p] = temp[p];
        }

    }
    void mergetsort(vector<int>& nums, int left, int right){
        if (left >= right) return;
        int first = left, last = right -1;
        int mid = left + (right - left) / 2;
        mergetsort(nums,left,mid);
        mergetsort(nums,mid+1,right);
        mergetCount(nums,left,mid,right);
    }

   



};

int main() {
    vector<int> nums = {34,66,2,5,95,4,46,27};
    Solution ob;
    ob.mergetsort(nums,0,nums.size());
    for (auto it: nums) {
        cout << it << "\t";
    }
    cout << endl;
}