#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    void swap(char& a, char& b) {
        char temp = a;
        a = b;
        b = temp;
    }
    void reverseString(vector<char>& s) {
        int left = 0, right = s.size() - 1;
        while(left <= right) {
            swap(s[left],s[right]);
            // cout<<s[left]<<"\t" <<s[right]<<endl;
            // break;
            left++;
            right--;
        }
    }
};

int main() {
    Solution ob;
    vector<char> s = {'h','e','l','l', 'o'};
    ob.reverseString(s);
    for(auto it = s.begin(); it != s.end(); it++) {
        cout <<*it <<"\t";
    }
    cout << endl;

}