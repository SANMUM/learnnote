#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<int> partitionLabels(string s) {
        int hash[27] = {0};
        for (int i = 0; i < s.size(); ++i) {
            hash[s[i]-'a'] = i;
        }
        int left = 0, right = 0;
        vector<int> result;
        for (int i = 0; i < s.size(); i++) {
           right = max(right, hash[s[i]-'a']);
           if (i == right){
                result.push_back(right-left+1);
                left = right + 1;
           }
        }
        return result;
    }
};

int main() {
    string s = "ababcbacadefegdehijhklij";
    Solution ob;
    vector<int> result = ob.partitionLabels(s);
    for (auto it : result) {
        cout << it << "\t";
    }
    cout << endl;
}