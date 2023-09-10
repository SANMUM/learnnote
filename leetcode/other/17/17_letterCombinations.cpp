#include<iostream>
#include<vector>
using namespace std;

void dfs(const string& s,const vector<string>& list,int cur,string t,vector<string>& ret){
    if( cur == s.length()){
        ret.push_back(t);
        return ;
    }
    int idx = s[cur] -'0' -2;
    for(char c: list[idx]){
        dfs(s,list,cur+1,t+c,ret);
    }

   }
vector<string> letterCombinations(string digits) {
    vector<string> ret;
    if (digits.empty()) return ret;
    
    vector<string> list = {"abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};
    dfs(digits,list,0,"",ret);
    return ret;


}