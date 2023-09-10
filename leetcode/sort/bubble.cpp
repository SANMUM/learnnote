#include <bits/stdc++.h>
using namespace std;
class Solution{
public:
    vector<int> bubblesort(vector<int>& nums){
        int len = nums.size();
        for (int j = len -1; j > 0; j--) {
            for (int i = 0; i <j; i++) {
                if (nums[i] > nums[i+1]) {
                    swap(nums[i], nums[i+1]);
                }
            }
        }
        return nums;
    }

    vector<int> bubblesort2(vector<int>& nums){
        int len = nums.size();
        bool is_swap;
        for (int i = 0; i < len; i++) {
            is_swap = false;
            for (int j = 1; j < len-i; j++) {
                if (nums[j] < nums[j-1]) {
                    swap(nums[j], nums[j-1]);
                    is_swap = true;
                }
            }
            if (!is_swap) break;
        }

        return nums;
    }



};

int main() {
    vector<int> nums = {34,66,2,5,95,4,46,27};
    Solution ob;
    vector<int> ret = ob.bubblesort2(nums);
    for (auto it: ret) {
        cout << it << "\t";
    }
    cout << endl;
}