#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int len = nums.size();
        vector<int> ret;
        for(int i = 0; i < len; i++){
            int value = nums[i] * nums[i];
            ret.push_back(value); 
        }
        sort(ret.begin(),ret.end());
        return ret;
    }
};
int main(){
    vector<int> nums = {-7,-3,2,3,11};
    Solution ob;
    vector<int> ret = ob.sortedSquares(nums);
    for(auto it = ret.begin(); it != ret.end(); it++){
        std::cout << *it << "\t";
    }
    std::cout << endl;
}