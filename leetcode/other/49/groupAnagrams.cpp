#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string,vector<string>> umap;
        vector<vector<string>> ret;
        // sort(strs.begin(),strs.end());
        for(int i=0;i < strs.size();i++){
            auto cit = strs[i];
            sort(strs[i].begin(),strs[i].end());
            umap[strs[i]].push_back(cit);
        }
        for(auto it = umap.begin();it != umap.end();it++){
            ret.push_back(it->second);
        }
        return ret;
    }
};

int main(){
    Solution ob;
    vector<string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};
    vector<vector<string>> ret = ob.groupAnagrams(strs);
    for(int i = 0;i<ret.size();i++){
        for(auto it = ret[i].begin();it!=ret[i].end();it++){
        cout<<*it<<"\t";
    }
    cout<<endl;
    }
    
        
}