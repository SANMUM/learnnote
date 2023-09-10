#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int maxdigit(vector<int>& nums) {
        int len = nums.size();
        int maxV = nums[0];
        for (int i = 1; i < len; i++) {
            if (nums[i] > maxV) {
                maxV = nums[i];
            }
        }
        int d = 1;
        int p = 10;
        while (maxV>=p) {
            maxV /= 10;
            d++;
        }
        return d;
    }
    void radixSort(vector<int>& nums) {
        int size = nums.size();
        int d = maxdigit(nums);
        vector<int> temp(size);
        vector<int> count(10,0);
        // int i,j,k;
        int radix = 1;
        for (int i = 1; i <= d; i++) {
            count.assign(10,0);
            for (int j = 0; j < size; j++) {
               int k = (nums[j] / radix ) % 10; // 记录桶的位置
               count[k]++;
            }
            for(int j= 1; j < 10; j++) {
                count[j] += count[j-1];
            }
            for (int j = size -1; j >= 0; j--) {
                int k = (nums[j]/radix) % 10;
                temp[count[k]-1] = nums[j]; // 从桶中取数据
                count[k]--;
            }
            for (int j=0; j < size; j++) {
                nums[j] = temp[j];
            }
            radix *= 10;
        }
    }
};

int main() {
    vector<int> nums = {2,4,1,2,5,3,4,8,7};
    // vector<float> nums = {0.78,0.17,0.39,0.26,0.72,0.94,0.21,0.12,0.23,0.68};
    Solution ob;
    // ob.heap_sort(nums,sizeof(nums)/sizeof(int));
    ob.radixSort(nums);
    for (auto it: nums) {
        cout << it << "\t";
    }
    cout << endl;
}