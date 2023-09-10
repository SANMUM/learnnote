#include<iostream>
#include<vector>
#include<string>
using namespace std;
string longestCommonPrefix(vector<string>& strs){
    int len_f = strs[0].length();
    for(int i=0;i<len_f;i++)
    {
        char ch = strs[0][i];
        for(int j=1;j<strs.size();j++){
            if( i > strs[j].length() || strs[j][i] != ch)
                return strs[0].substr(0,i);
        }
    }
    return strs[0];

}

int main(){
    vector<string> input = {"flower","flow","flight"}

}