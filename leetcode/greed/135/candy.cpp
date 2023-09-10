#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int candy(vector<int>& ratings) {
        int result = 0;
        int len = ratings.size();
        vector<int> candyVec(len, 1);
        for (int i = 1; i < len; i++) {
            if (ratings[i] > ratings[i - 1]) {
                candyVec[i] = candyVec[i-1] + 1;
            }
        }
        for (int i = len - 2; i >= 0; i--) {
            if (ratings[i] > ratings[i+1]) {
                candyVec[i] = max(candyVec[i+1]+1, candyVec[i]);
            }
        }
        for (auto it : candyVec) {
            result += it;
        }
        return result;

    }
};
int main() {
    Solution ob;
    vector<int> nums = {1,0,2};
    int ret = ob.candy(nums);
    cout << ret << endl;
}