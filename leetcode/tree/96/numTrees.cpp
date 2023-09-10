#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    int numTrees(int n) {
        vector<int> dp(n+1,0);
        dp[0] = 1;
        for (int i = 0; i <= n; i++) {
            for (int j = 1; j <= i; j++) {
                dp[i] += dp[j-1]* dp[i-j];
            }
        }
        return dp[n];   
    }
};

int main() {
    Solution ob;
    int result = ob.numTrees(5);
    cout << result << std::endl;
}