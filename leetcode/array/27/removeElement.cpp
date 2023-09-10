#include<iostream>
#include<vector>
using namespace std;
// int removeElement(vector<int>& nums, int val) {
//     vector<int>::iterator it = nums.begin();
//     while( it != nums.end()){
//         if(*it == val){
//             nums.erase(it);
//         }
//         else{
//             it++;
//         }
//     }
//     return nums.size();
// }

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int slowIndex = 0;
        for (int fastIndex = 0; fastIndex < nums.size(); fastIndex++) {
            if (val != nums[fastIndex]) {
                nums[slowIndex++] = nums[fastIndex];
            }
        }
        return slowIndex;
    }
};
int main(){
    Solution ob;
    vector<int> nums = {3,2,2,3};
    int val = 3;
    int k = ob.removeElement(nums,val);
    cout << k << endl;
    // for (size_t i = 0; i < k; i++)
    // {
    //     cout<<nums[i]<<"\t";
    // }
    // cout<<"\n";
    
}