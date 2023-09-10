#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    string countAndSay(int n) {
       string prev = "1"; 
       for(int i=1;i<n;i++){
            string cur = "";
            int start = 0;
            int pos = 0;
            while(pos<prev.size()){
                while(pos<prev.size()&& prev[pos] == prev[start]){
                    pos++;
                }
                cur += to_string(pos-start)+prev[start];
                start = pos;
            }
            prev = cur;
       }
       return prev;
        
    }
};

int main(){
    Solution ob;
    int n = 5;
    string ret = ob.countAndSay(n);
    cout<<ret<<endl;
}