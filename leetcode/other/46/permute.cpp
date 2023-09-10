#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    void dfs(vector<int>&nums,vector<bool> used){
        if(combine.size() == nums.size()){
            ret.push_back(combine);
            return;
        }
        for(int i=0;i<nums.size();i++){
            if(used[i] == true) continue;
            used[i] = true;
            combine.push_back(nums[i]);
            // swap(nums[i],nums[0]);
            printf("before dfs => " );
            ss_cout(combine);
            dfs(nums,used);
            // swap(nums[i],nums[0]);
            used[i] = false;
            combine.pop_back();
            printf("after dfs =>" );
            ss_cout(combine);
        }
        
    }
    vector<vector<int>> permute(vector<int>& nums) {
        vector<bool> used(nums.size(),false);
        dfs(nums,used);
        return ret;
    }
    vector<vector<int>> ret;
    vector<int> combine;
    void ss_cout(vector<int> array){
    for(auto it = array.begin(); it!=array.end();it++){
        cout<<*it<<"\t";
    }
    cout<<endl;
   }
};

int main(){
    vector<int> nums = {1,2,3};
    Solution ob;
    vector<vector<int>> ret =  ob.permute(nums);
    for(int i = 0;i<ret.size();i++){
        for(auto it=ret[i].begin();it != ret[i].end();it++){
            cout<<*it<<"\t";
        }
        cout<<endl;
        // for(int j = 0;j<ret[0].size();j++){
        //     cout<<ret[i][j]<<"\t";
        }
}