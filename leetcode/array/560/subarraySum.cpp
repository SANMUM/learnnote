#include<bits/stdc++.h>
using namespace std;
// class Solution {
// public:
//     int subarraySum(vector<int>& nums, int k) {
        
//         int count = 0;
//         for (int start = 0; start < nums.size(); start++) {
//             int sum = 0;
//             for (int end = start; end >=0 ; end--) {
//                 sum += nums[end];
//                 if (sum == k) {
//                     count++;
//                 }
//             }
//         }
//         return count;
//     }
// };

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        
        int count = 0;
        unordered_map<int, int> umap;
        umap[0] = 1;
        int pre = 0;
        for (int start = 0; start < nums.size(); start++) {
            pre += nums[start];
            if (umap.find(pre - k) != umap.end()) {
                count += umap[pre-k];
            }
            umap[pre]++;
        }
        return count;
    }
};
int main(){
    vector<int> nums = {1,1,1};
    int k = 2;
    Solution ob;
    int ret = ob.subarraySum(nums, k);
    cout << ret << endl;
}