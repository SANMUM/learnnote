#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int sLen = s.size();
        int pLen = p.size();
        if (sLen < pLen) {
            return {};
        }
        vector<int> pCount(26,0);
        vector<int> sCount(26,0);
        vector<int> result;
        for (int i = 0; i < pLen; i++) {
            pCount[p[i]-'a']++;
            sCount[s[i]-'a']++;
        }
        if (pCount == sCount) {
            result.push_back(0);
        }
        for (int i = 0; i < sLen - pLen; i++) {
            sCount[s[i]-'a']--;
            sCount[s[i+pLen]-'a']++;

            if (sCount == pCount) {
                result.push_back(i+1);
            }
        }
        return result;
    }
};
int main() {
    string s = "cbaebabacd",p = "abc";
    Solution ob;
    vector<int> ret = ob.findAnagrams(s, p);
    for (auto it : ret) {
        cout << it  << " ";
    }
    cout << endl;
}