#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void removeEmpty(string& s) {
        int slow = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] != ' ') {
                if (slow != 0) s[slow++] = ' ';
                while (i < s.size() && s[i] != ' ') {
                    s[slow++] = s[i++];
                }
            }
        }
        s.resize(slow);
    }
    void reversed(string& s, int start, int end) {
        for(int i = start, j = end; i < j; i++, j--) {
            swap(s[i],s[j]);
        }
    }
    string reverseWords(string s) {
        removeEmpty(s);
        reversed(s, 0, s.size() - 1);
        int start = 0;
        for (int i = 0; i <= s.size(); i++) {
            if (s[i] == ' ' || i == s.size() ) {
                reversed(s, start,i-1);
                // s[i] = ' ';
                start = i+1;
            }
        }
        return s;
    }
};

int main() {
    ::string s = "the sky is blue";
    Solution ob;
    ::string ret = ob.reverseWords(s);
    ::cout << ret << ::endl;
}