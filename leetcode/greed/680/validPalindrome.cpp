#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool isPalindrome(string s, int start, int end) {
        for (int i = start, j = end; i < j; i++, j--) {
            if (s[i] != s[j]) {
                return false;
            }
        }
        return true;
        
    }
    bool validPalindrome(string s) {
        int low = 0;
        int high = s.size() - 1;
        while (low < high) {
            if (s[low] == s[high]) {
                high--;
                low++;
            }
            else {
                return isPalindrome(s,low, high -1) || isPalindrome(s, low+1,high);
            }
        }
        return true;
    }
};

int main() {
    ::string s = "abca";
    Solution ob;

    bool ret = ob.validPalindrome(s);
    ::cout << ::boolalpha;
    ::cout << ret << ::endl;
}