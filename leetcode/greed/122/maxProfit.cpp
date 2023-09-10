#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int len = prices.size();
        int sum = 0;
        for (int i = 0; i < len - 1; i++ ) {
            int diff = prices[i+1] - prices[i];
            if (diff > 0) {
                sum +=  diff;
            }
        }
        return sum;
    }
};

int main() {
    Solution ob;
    vector<int> prices = {7,1,5,3,6,4};
    int ret = ob.maxProfit(prices);
    cout << ret << endl;
}