#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        int result = 0;
        int index = s.size() - 1;
        for (int i = g.size() - 1; i >= 0; i--) {
            if(index>=0 && s[index] >= g[i]) {
                result++;
                index--;
            }
        }
        return result;
    }
};

int main() {
    Solution ob;
    vector<int> g = {1,2};
    vector<int> s = {1,2,3};
    int ret = ob.findContentChildren(g,s);
    ::cout << ret << ::endl;
}