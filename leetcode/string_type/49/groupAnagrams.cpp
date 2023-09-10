#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> result;
        unordered_map<string, vector<string>> umap;
        for (auto str : strs) {
            auto it = str;
            sort(it.begin(), it.end());
            umap[it].push_back(str);
        }
        for (auto it : umap) {
            result.push_back(it.second);
        }
        return result;
    }
};

int main() {
    Solution ob;
    vector<string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};
    vector<vector<string>> ret = ob.groupAnagrams(strs);
    for (int i = 0; i < ret.size(); i++) {
        for (auto it : ret[i]) {
            cout << it << "\t";
        }
        cout << endl;
    }
}