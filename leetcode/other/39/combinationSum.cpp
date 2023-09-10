#include<bits/stdc++.h>
using namespace std;
// class Solution {
// public:
//     // vector<vector<int>> ret ;
//     void dfs(vector<int>& search,int target ,vector<vector<int>>& ret,vector<int>& combine, int idx){
//         if(idx == search.size()){
//             return ;
//         }
//         if(target == 0){
//             // ret.push_back(combine);
//             ret.emplace_back(combine);
//             return;
//         }
//         dfs(search,target,ret,combine,idx+1);
//         if(target-search[idx]>=0){
//             // combine.push_back(search[idx]);
//             combine.emplace_back(search[idx]);
//             dfs(search,target-search[idx],ret,combine,idx);
//             combine.pop_back();
//         }
//     }
//     vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
//         vector<vector<int>> ret;
//         vector<int> combine;
//         dfs(candidates,target,ret,combine,0);
//         return ret;
//     }
// };



class Solution {
private:
    vector<vector<int>> result;
    vector<int> path;
    void backtracking(vector<int>& candidates, int target, int sum, int startIndex) {
        if (sum > target) {
            return;
        }
        if (sum == target) {
            result.push_back(path);
            return;
        }

        for (int i = startIndex; i < candidates.size(); i++) {
            sum += candidates[i];
            path.push_back(candidates[i]);
            backtracking(candidates, target, sum, i); // 不用i+1了，表示可以重复读取当前的数
            sum -= candidates[i];
            path.pop_back();
        }
    }
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        result.clear();
        path.clear();
        backtracking(candidates, target, 0, 0);
        return result;
    }
};

int main(){
    vector<int> nums = {2,3,5};
    int target = 7;
    Solution ob;
    vector<vector<int>> ret = ob.combinationSum(nums,target);
    for(int i = 0;i<ret.size();i++){
        for(auto it=ret[i].begin();it != ret[i].end();it++){
            cout<<*it<<"\t";
        }
        cout<<endl;
        // for(int j = 0;j<ret[0].size();j++){
        //     cout<<ret[i][j]<<"\t";
        }
        
    }

