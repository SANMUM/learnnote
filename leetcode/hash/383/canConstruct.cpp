#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    void get_count(string str, unordered_map<char,int> &umap) {
        for(char ch : str){
            umap[ch]++;
        }
    }
    bool canConstruct(string ransomNote, string magazine) {
        unordered_map<char,int> ra_count;
        unordered_map<char,int> ma_count;
        get_count(ransomNote, ra_count);
        get_count(magazine, ma_count);
        for(char ch: ransomNote ){
            if(ma_count.find(ch) == ma_count.end()) {
                return false;
            }
            else{
                if(ma_count[ch]>= ra_count[ch]){
                    continue;
                }
                else{
                    return false;
                }
            }
        }
        return true;
    }

};

int main() {
    Solution ob;
    string ransomNote = "aa", magazine = "aab";
    bool ret = ob.canConstruct(ransomNote,magazine);
    cout<< boolalpha;
    cout<<ret<<endl;
}