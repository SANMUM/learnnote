#include<iostream>
#include<vector>

using namespace std;
int removeDuplicates(vector<int>& nums) {
    for (auto  it = nums.begin()+1; it !=nums.end(); )
    {
        int pre  = *(it-1);
        if(*it == pre){
            nums.erase(it);
        }
        else{
            it++;
        }
    }
    return nums.size();
    
}
int main(){
    vector<int> nums = {1,1,1,2,3};
    int k = removeDuplicates(nums);
    cout<<k;
    for (size_t i = 0; i < k; i++)
    {
        cout<<nums[i]<<"\t";
    }
    cout<<"\n";
    
}