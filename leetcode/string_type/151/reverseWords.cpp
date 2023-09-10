#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    void reverse(string &str, int start, int end) {
        for (int i = start, j=end; i < j; i++,j--)
        {
            swap(str[i], str[j]);
        }
        
    }
    void removeExtraBlank(string& str) {
        int len = str.length();
        int size = 0;
        for (int i = 0; i < len; ++i)
        {
            if(str[i] != ' '){ // 遇到非空格开始处理
                if(size != 0) {
                    str[size++] = ' ';
                }
                while (i < len && str[i] != ' ') { //碰到下一次空格处处理
                    str[size++] = str[i++];
                }
            }
        }
        str.resize(size);
        
    }
    string reverseWords(string s) {
        
        removeExtraBlank(s); // 移除额外的空格
        int len = s.length();
        // cout<<s<<endl;
        reverse(s, 0, len-1);
        // cout<<s<<endl;
        // cout<<s<<'\t'<<s.length()<<endl;
        int slowIndex = 0;
        for (int i = 0; i<=len; i++) {
            if(i==len || s[i] == ' '){
                reverse(s, slowIndex, i-1);
                slowIndex = i+1;
            }
        }
        return s;
    }
};

int main() {
    string s = "a good   example";
    Solution ob;
    string ret = ob.reverseWords(s);
    cout<<ret<<'\t'<<endl;
}