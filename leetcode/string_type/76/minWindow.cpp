#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int scnt[128], tcnt[128];
    bool check() {
        for (int i = 0; i < 128; i++) {
            if (scnt[i] < tcnt[i]) {
                return false;
            }
        }
        return true;
    }
    string minWindow(string s, string t) {
        memset(scnt, 0, sizeof(scnt));
        memset(tcnt, 0, sizeof(tcnt));
        // for (int i = 0; i < t.size(); i++) {
        //     tcnt[t[i]]++;
        // }
        for (char it : t) {
            tcnt[it]++;
        }
        int n = s.size();
        int minLen= n + 1;
        int left = -1, right = -1;
        int l = 0, r = 0;
        while (r < n) {
            scnt[s[r++]]++;
            while (check()) {
                if (r - l < minLen) {
                    minLen = r - l;
                    left = l;
                    right = r - 1;    
                }
                scnt[s[l++]]--;
            }
        }
        // if (left == -1) return "";
        // return s.substr(left, right-left+1);
        return left == -1 ? "": s.substr(left,right-left+1);
    }
};

int main() {
    string s = "ADOBECODEBANC", t = "ABC";
    Solution ob;
    string ret = ob.minWindow(s, t);
    // cout << s.substr(1,5);
    cout << ret << endl;
    

}