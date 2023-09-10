#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int len = cost.size();
        // int dp[len+1] = {0};
        // dp[i]到达第i台阶所花费的最少体力
        vector<int> dp(len+1, 0);
        dp[0] = dp[1] = 0;
        for (int i = 2; i <= len; i++) {
            dp[i] = min(dp[i-1]+ cost[i-1], dp[i-2]+cost[i-2]);
        }
        printvector(dp);
        return dp[len];
    }

    void printvector(vector<int>& nums) {
        for (auto it : nums) {
            cout << it << "\t";
        }
        cout << endl;
    }
};

int main() {
    vector<int> cost = {1,100,1,1,1,100,1,1,100,1};
    Solution ob;
    int ret = ob.minCostClimbingStairs(cost);
    cout << ret << endl;
}