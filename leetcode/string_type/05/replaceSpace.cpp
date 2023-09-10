#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    string replaceSpace(string s) {
        int oldSize = s.length();
        int count = 0;
        for (int i = 0; i < oldSize; i++) {
            if (s[i] == ' ') {
                count++;
            }
        }
        s.resize(oldSize + 2*(count));
        int newSize = s.length();
        for (int i = newSize - 1, j = oldSize - 1; j < i; j--,i--) {
            if (s[j] != ' ') {
                s[i] = s[j];
            }
            else{
                s[i] = '0';
                s[i - 1] = '2';
                s[i- 2 ] = '%';
                i -= 2;
            }   
        }
        return s;
    }
};

int main() {
    string s = "We are happy.";
    Solution ob;
    string ret = ob.replaceSpace(s);
    cout<<ret<<endl;
}