#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {
        int five = 0, ten = 0;
        for (auto it : bills) {
            if (it == 5) {
                five++;
            }
            else if (it == 10) {
                if (five > 0) {
                    five--;
                    ten++;
                }
                else {
                    return false;
                }
            }
            else {
                if (five > 0 && ten > 0) {
                    ten--;
                    five--;
                }
                else if (five >= 3) {
                    five -= 3;
                }
                else {
                    return false;
                }
            }
        }
        return true;
    }
};

int main() {
    vector<int> nums = {5,5,10,20,5,5,5,5,5,5,5,5,5,10,5,5,20,5,20,5};
    Solution ob;
    bool result = ob.lemonadeChange(nums);
    cout << boolalpha;
    cout << result << endl;

}