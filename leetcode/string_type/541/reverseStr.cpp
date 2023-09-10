#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    string reverseStr(string s, int k) {
        int len = s.length();
        int gap = 2*k;
        for (int i = 0; i < len; i += gap) {
            if(i + k < len) {
                reverse(s.begin()+i, s.begin()+i+k);
            }
            else {
                reverse(s.begin()+i, s.end());
            }
        }
        return s;
        
    }
};

int main() {
    string s = "abcdefg";
    int k = 2;
    Solution ob;
    string ret = ob.reverseStr(s,k);
    cout<<ret<<endl;
}