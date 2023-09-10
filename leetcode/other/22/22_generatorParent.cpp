#include<iostream>
#include<vector>
using namespace std;
char buf[18]={0};
vector<string> res;
void dfs(int left,int right,int cur){
    if(!left && !right) {
        res.push_back(buf);
        return ;
    }
    if(left){
        buf[cur] = '(';
        dfs(left-1,right,cur+1);
    }
    if(right> left){         
        buf[cur]=')';
        dfs(left,right-1,cur+1);
    }
    
}
vector<string> generateParenthesis(int n) {
    dfs(n,n,0);
    return res;
}
int main(){
    int n = 3;
    generateParenthesis(n);
    // buf[0]='(';
    // buf[8]='(';
    for(int i=0;i<res.size();i++)
        cout<<res[i]<<"\n";
    // cout<<res<<endl;
}