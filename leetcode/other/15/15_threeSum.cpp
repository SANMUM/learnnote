#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
vector<vector<int>> threeSum(vector<int>& nums) {
    sort(nums.begin(),nums.end());
    int num_len = nums.size();
    int j,r;
    int three_sum;
    vector<vector<int>> res;
    int preid = -1;
    for(int i=0;i<num_len;i++)
    {
        j = i + 1;
        r = num_len - 1;

        if(preid != -1 && nums[i] == nums[preid]) continue;
        while (j<r)
        {
            three_sum = nums[i] + nums[j] + nums[r];
            if(three_sum == 0)
            {
                res.push_back({nums[i],nums[j],nums[r]});
                int k = nums[j];
                while(j<r && k == nums[j]) j++;
            }
            else if(three_sum < 0)
            {
                j++;
            }
            else
            {
                r--;
            }
            
        }
        preid = i;
    }
    return res;

}

int main(){
    vector<int> nums = {-1,0,1,2,-1,-4};
    vector<vector<int>> ret;
    ret = threeSum(nums);
    int c_len = ret.size();
    for(int i= 0; i<c_len;i++)
    {
        for (int j = 0; j < ret[1].size(); j++)
        {
            cout<<ret[i][j]<<"\t";
        }
    cout<<endl;
    }
}