#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> uset;
        for (auto it : nums) {
            uset.insert(it);
        }
        
        int maxLen = 0;
       for (auto it : uset) {
            if (!uset.count(it-1)) {
                int curNum = it;
                int curLen = 1;
                while (uset.count(curNum+1)) {
                    curNum++;
                    curLen++;
                }
                maxLen = max(maxLen, curLen);
            }
       }
       return maxLen;
    }
};

int main() {
    vector<int> nums = {0,3,7,2,5,8,4,6,0,1};
    Solution ob;
    int ret = ob.longestConsecutive(nums);
    cout << ret << endl;
}