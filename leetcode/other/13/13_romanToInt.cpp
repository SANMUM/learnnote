#include<iostream>
#include<string>
#include<unordered_map>

using std::unordered_map;
using std::string;
using std::cout;
using std::endl;
int romanToInt(string s) {
    int sum = 0;
    unordered_map<char,int> roman = {{'I',1}, {'V',5},{'X',10},{'L',50},{'C',100},{'D',500},{'M',1000}};
    int len = s.length();
    for (int i = 0; i < len; i++)
    {
        char ch = s[i];
        int val = roman[ch];
        if((i+1)<len){
            if((ch=='I') && (s[i+1] == 'V' || s[i+1] == 'X' ))
                {
                    val-=2;
                    cout<<val<<endl;
                }
            if((ch=='X') && (s[i+1] == 'L' || s[i+1] == 'C' ))
                val-=20;
            if((ch=='C') && (s[i+1] == 'D' || s[i+1] == 'M' ))
                val-=200;
        }
        sum += val; 
    }
    return sum;
}

int main(){
//    string s = "III";
//    string s = "IX";
    // string s = "LVIII";
    string s = "MCMXCIV";
   int res;
   res = romanToInt(s);
   cout << res<<endl; 
}