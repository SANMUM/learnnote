#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    void backtracking(vector<int>& nums,vector<bool> used){
        if(combine.size() == nums.size()){
            ret.push_back(combine);
            return;
        }
        for(int i=0; i< nums.size();i++){
            if(i>0&& nums[i] == nums[i-1] && used[i-1] == false) continue;
            if(used[i]==false){
                 combine.push_back(nums[i]);
            used[i] = true;
            // swap(nums[start],nums[i]);
            backtracking(nums,used);
            used[i] = false;
            // swap(nums[i],nums[start]);
            combine.pop_back();
            }
           
        }
    }
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<bool> used(nums.size(),false);
        sort(nums.begin(),nums.end());
        backtracking(nums,used);
        return ret;
    }
    vector<vector<int>> ret;
    vector<int> combine;
};

int main(){
    vector<int> nums = {1,1,3};
    Solution ob;
    vector<vector<int>> ret =  ob.permuteUnique(nums);
    for(int i = 0;i<ret.size();i++){
        for(auto it=ret[i].begin();it != ret[i].end();it++){
            cout<<*it<<"\t";
        }
        cout<<endl;
        // for(int j = 0;j<ret[0].size();j++){
        //     cout<<ret[i][j]<<"\t";
        }
}