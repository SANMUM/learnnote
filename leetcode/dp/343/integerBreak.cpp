#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int integerBreak(int n) {
        int dp[58] = {0};
        dp[2] = 1;
        for (int i = 3; i <= n; i++) {
            for (int j = 1; j <= i/2; j++) {
                dp[i] = max(max(j*(i-j),j*dp[i-j]),dp[i]);
            }
        }
        return dp[n];

    }
};

int main() {
    int n = 10;
    Solution ob;
    int ret = ob.integerBreak(n);
    cout << ret << endl;
}
