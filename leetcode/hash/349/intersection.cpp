#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> ret;
        int hash[1000] = {0};
        for(auto num : nums1) {
            hash[num] = 1;
        }
        for(auto num: nums2) {
            if(1 == hash[num]){
                ret.insert(num);
            }
        }
        return vector<int>(ret.begin(),ret.end());
    }
};

int main() {
    vector<int> nums1 = {4,9,5};
    vector<int> nums2 = {2,8,9,4};
    Solution ob;
    vector<int> ret = ob.intersection(nums1,nums2);
    for(auto it: ret) {
        cout<< it<<"\t";
    }
    cout<<endl;

}