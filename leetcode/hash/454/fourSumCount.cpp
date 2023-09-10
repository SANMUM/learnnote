#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
        unordered_map<int,int> umap;
        int ret = 0;
        for(auto a : nums1) {
            for(auto b : nums2){
                umap[a+b]++;
            }
        }
        for(auto c : nums3) {
            for(auto d : nums4){
                if(umap.find(0-(c+d)) != umap.end()){
                    ret += umap[0 - (c + d)];
                }
            }
        }
        return ret;

    }
};

int main() {
    Solution ob;
    vector<int> nums1 = {1,2};
    vector<int> nums2 = {-2,-1};
    vector<int> nums3 = {-1,2};
    vector<int> nums4 = {0,2};
    // int ret = ob.fourSumCount(nums1,nums2,nums3,nums4);
    // cout<<ret;
    // auto it = nums1.find(2);
    unordered_multimap<int,int> umap = {{1,2},{3,4},{1,5}};
    auto it = umap.count(1);
    // cout<<it->first<<"\t"<<it->second;
    cout<<it;
    cout<<endl;
    

}