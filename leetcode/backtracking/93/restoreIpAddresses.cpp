#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    void backtracking(string& s, int index, int pointnum) {
        if (pointnum == 3) {
            if (isValid(s, index, s.size() - 1)) {
                ret.push_back(s);
            }
            return;
        }

        for (int i = index; i < s.size(); i++) {
            if (isValid(s,index, i)) {
                s.insert(s.begin()+i+1,'.');
                backtracking(s,i+2,pointnum+1);
                s.erase(s.begin()+i+1);
            }
            else {
                break;
            }
        }
    }
    vector<string> restoreIpAddresses(string s) {
        backtracking(s, 0, 0);
        return ret;
    }
    bool isValid(string& s, int start, int end) {
        if (start > end) {
            return false;
        }
        if (s[start] == '0' && start != end) {
            return false;
        }
        int num  = 0;
        for(int i = start; i <= end; i++) {
            if (s[i] > '9' || s[i] < '0') {
                return false;
            }
           num  = num*10 + (s[i] - '0');
           if (num > 255) {
            return false;
           }
        }
        return true;
    }

private:
vector<string> ret;
};
int main() {
    Solution ob;
    string s = "25525511135";
    vector<string> ret = ob.restoreIpAddresses(s);
    for(auto it : ret) {
        cout << it << endl;
    }
}