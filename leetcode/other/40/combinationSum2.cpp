#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    void dfs(vector<int>& candidates,int target,int sum,int idx){
        // if(sum>target){
        //     return;
        // }
        if(sum == target){
            ret.push_back(combine);
            return;
        }

        for(int i=idx;i<candidates.size()&& sum+candidates[i]<=target;i++){
            // if(i>idx && candidates[i] == candidates[i-1]){
            //     continue;
            // }
            sum += candidates[i];
            combine.push_back(candidates[i]);
            
            dfs(candidates,target,sum,i+1);
            sum -= candidates[i];
            combine.pop_back();
        }

    }
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        
        sort(candidates.begin(),candidates.end());
        dfs(candidates,target,0,0);
        return ret;

    }

    vector<vector<int>> ret;
    vector<int> combine;
};

int main(){
    vector<int> nums = {10,1,2,7,6,1,5};
    int target = 8;
    Solution ob;
    vector<vector<int>> ret = ob.combinationSum2(nums,target);
    for(int i = 0;i<ret.size();i++){
        for(auto it=ret[i].begin();it != ret[i].end();it++){
            cout<<*it<<"\t";
        }
        cout<<endl;
        // for(int j = 0;j<ret[0].size();j++){
        //     cout<<ret[i][j]<<"\t";
        }
        
}