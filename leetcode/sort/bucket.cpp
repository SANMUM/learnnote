#include <bits/stdc++.h>
using namespace std;
class Solution{
public:
    void bucketSort(vector<int>& nums) {
        if (nums.empty()) return;
        int low = *::min_element(nums.begin(),nums.end());
        int high = *::max_element(nums.begin(), nums.end());
        int n = high - low + 1;
        vector<int> bucket(n);
        vector<int> res;
        for (auto x: nums) {
            bucket[x-low]++;
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < bucket[i]; ++j) {
                res.push_back(i+low);
            }
        }
        for (auto it : res) {
            ::cout << it << ::endl;
        }
    }

    void bucketSort(vector<float>& nums) {
        if (nums.empty()) return;
        int size = nums.size();
        vector<vector<float>> res(size);  // 有size个元素就分配size个桶
        for (int i = 0; i < size; i++) {
            int bi = size*nums[i];
            res[bi].push_back(nums[i]);
        }
        for (int i=0; i < size; i++) {
            sort(res[i].begin(),res[i].end());
        }
        int index = 0;
        for (int i = 0; i < size;i++) {
            for (int j = 0; j < res[i].size(); j++) {
                nums[index++] = res[i][j];
            }
        }
        for (auto it : nums) {
            ::cout << it << ::endl;
        }
    }
};

int main() {
    // vector<int> nums = {34,66,2,5,95,4,46,27};
    vector<float> nums = {0.78,0.17,0.39,0.26,0.72,0.94,0.21,0.12,0.23,0.68};
    Solution ob;
    // ob.heap_sort(nums,sizeof(nums)/sizeof(int));
    ob.bucketSort(nums);
    // for (auto it: nums) {
    //     cout << it << "\t";
    // }
    cout << endl;
}