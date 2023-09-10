#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        // vector<int>::iterator it;
        for (auto it = nums.begin(); it != nums.end();){
            // std::cout<<*it<<'\t';
            if(*it == val){
                nums.erase(it);
            }
            else {
                it++;
            }
        }
        return nums.size();
}
};

int main(){
    vector<int> nums = {0,1,2,2,3,0,4,2};
    int val = 2;
    Solution ob;
    int ret = ob.removeElement(nums,val);
    std::cout << ret << endl;
}