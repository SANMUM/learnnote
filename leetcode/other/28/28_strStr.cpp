#include<iostream>
#include<string>
#include<vector>
using namespace std;

int strStr(string haystack, string needle) {
    int n_len = needle.length();
    int h_len = haystack.length();
    int i = 1;
    // int j = 1;
    int prefix_len = 0;
    vector<int> next = {0};
    while(i < n_len){
        if(needle[prefix_len] == needle[i]){
            i++;
            prefix_len +=1;
            next.push_back(prefix_len);
            // j++;
        }
        else
        {
            if(prefix_len == 0){
                i++;
                next.push_back(prefix_len);
            }
            else{
                prefix_len = next[prefix_len-1];
            }
        }
    }
    for(int k=0;k<next.size();k++){
        cout<<next[k]<<"\t";
    }
    int l=0,r=0;
    while(l<h_len){
        if(haystack[l] == needle[r]){
            l++;
            r++;
        }
        else if(r>0){
            r = next[r-1];
        }
        else{
            l++;
        }

        if(r == n_len){
            return l-r;
        }
    }
    return -1;
}

// int main(){
//     // string txt = "aaacaaab", pat = "aaab";
//     // string txt = "ABCABCD",pat = "ABCABCD";
//     // string txt = "leetcode",pat = "leeto";
//     string txt = "mississippi",pat = "issip";
//     // string pat = "ABACABAB";
//     // int ret = search(txt,pat);
//     int ret = strStr(txt,pat);
//     // int next[10]={0};
//     // Getnext(next,pat);
//     // const int len_s = pat.length(); 
//     // int *next = new int[len_s]();
//     // next = build_next(pat);
//     // while (next)
//     // {
//     //     cout<<*next<<"\t";
//     //     next++;
//     // }
    
    
//     cout<<ret<<endl;
// }

int main(){
    string haystack = "leetcode", needle = "leeto";
    int ret = strStr(haystack,needle);
    cout<<ret<<endl;
}