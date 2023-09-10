#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    void backtrace(string& s, int startIndex) {
        if (startIndex >= s.size()) {
            ret.push_back(path);
            return;
        }
        for (int i = startIndex; i < s.size(); i++) {
            if (ispalinfrome(s,startIndex,i)) {
                string str = s.substr(startIndex, i- startIndex + 1);
                path.push_back(str);
            }
            else {
                continue;
            }
            backtrace(s, i+1);
            path.pop_back();

        }
    }
    vector<vector<string>> partition(string s) {
        backtrace(s, 0);
        return ret;
    }
    bool ispalinfrome(string s, int start, int end) {
        for (int i = start, j = end; i < j; i++,j--) {
            if (s[i] != s[j]) {
                return false;
            }
        }
        return true;
    }

private:
vector<vector<string>> ret;
vector<string> path;
};
int main() {
    Solution ob;
    string s = "aab";
    vector<vector<string>> ret = ob.partition(s);
    for (int i = 0; i < ret.size(); i++) {
        for(auto it : ret[i]){
            cout << it << "\t";
        }
        cout << endl;
    }
}