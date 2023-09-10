#include<iostream>
#include<stack>
#include<string>
#include<unordered_map>
using namespace std;

bool isValid(string s) {
    
    // cout<<s;
    unordered_map<char,char> map = {
        {')','('},
        {']','['},
        {'}','{'}
    };
    
    stack<char> stk;
    // // int len = s.length();
    for(auto ch:s){
        // cout<<map.count(ch);
        if(map.count(ch)){
            if(stk.empty() || stk.top() != map[ch]){
            return false;
        }
            stk.pop();
        }
        else{
            stk.push(ch);
        }
    }

    return stk.empty();
}

int main(){
    string s = "()[]{}";
    bool res = isValid(s);
    cout<<res<<endl;
}