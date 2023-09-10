#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    void dfs(vector<int> &nums,int len,int depth,vector<int> &path, vector<bool> &used, vector<vector<int>> &res){
        if( depth ==  len){
            res.push_back(path);
            return;
        }
        for(int i = 0; i < len;i++){
            if(!used[i]){
                path.push_back(nums[i]);
                used[i] = true;
                printf("before dfs => " );
                ss_cout(path);
                printf("before cout tr ");

                ss_cout(used);
                dfs(nums,len,depth+1,path,used,res);
                used[i] = false;
                path.pop_back();
                printf("after dfs => " );
                ss_cout(path);
                printf("after cout tr ");

                ss_cout(used);
            }
        }

    }
    vector<vector<int>> permute(vector<int>& nums) {
        int len = nums.size();
        vector<vector<int>> res;
        if ( len == 0){
            return res;
        }
        vector<bool> used(nums.size(),false);
        vector<int> path;
        // dfs(nums,used);
        dfs(nums,len,0,path,used,res);
        return res;
    }
    

   void ss_cout(vector<int> array){
    for(auto it = array.begin(); it!=array.end();it++){
        cout<<*it<<"\t";
    }
    cout<<endl;
   }
   void ss_cout(vector<bool> array){
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