#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int result = 0;
        int left = 0;
        unordered_map<char, int> umap;
        for (int right = 0; right < s.size(); right++) {
            umap[s[right]]++;
            while (umap[s[right]] >=2) {
             
                umap[s[left]]--;
                left++;
            }
            result = max(right-left+1, result);
        }
        return result;
        
    }
};

int main() {
    Solution ob;
    string s = "bbbbbacd";
    int ret = ob.lengthOfLongestSubstring(s);
    cout << ret << endl;
}