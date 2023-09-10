#include <bits/stdc++.h>
using namespace std;
// class Solution {
// public:
//     int climbStairs(int n) {
//         if ( n <= 2) return n;
        
//         return climbStairs(n-2) + climbStairs(n-1);
//     }
// };

// dp表示到达i阶有dp[i]种方法
// class Solution {
// public:
//     int climbStairs(int n) {
//         if (n <= 1) return n; // 因为下面直接对dp[2]操作了，防止空指针
//         vector<int> dp(n + 1);
//         dp[1] = 1;
//         dp[2] = 2;
//         for (int i = 3; i <= n; i++) { // 注意i是从3开始的
//             dp[i] = dp[i - 1] + dp[i - 2];
//         }
//         return dp[n];
//     }
// };
class Solution {
public:
    int climbStairs(int n) {
        if (n <= 1) return n;
        int dp[3];
        dp[1] = 1;
        dp[2] = 2;
        for (int i = 3; i <= n; i++) {
            int sum = dp[1] + dp[2];
            dp[1] = dp[2];
            dp[2] = sum;
        }
        return dp[2];
    }
};

int main() {
    Solution ob;
    int ret = ob.climbStairs(45);
    cout << ret << endl;
}