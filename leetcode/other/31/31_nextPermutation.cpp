#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
// void nextPermutation(vector<int>& nums) {
//     int len = nums.size()-1;
//     int k = -1;
//     int i = 0;
//     for(int i = len;i >=1 ;i--){
//         if(nums[i] > nums[i-1]){
//             k = i;
//             break;
//         }
//     }
//     if(k == -1){
//         reverse(nums.begin(),nums.end());
//     }
//     else{
//         reverse(nums.begin(),nums.begin()+k);
//         reverse(nums.begin()+k-1,nums.end());
//     }
//     printf("%d\n",k);
// }

void nextPermutation(vector<int>& nums) {
    int i = nums.size() - 2;
    while(i>=0 && nums[i] >= nums[i+1]){
        i--;
    }

    if(i>=0){
        int j = nums.size() - 1;
        while(j>=0 && nums[i] >= nums[j]){
            j--;
        }
        swap(nums[i],nums[j]);
    }
    reverse(nums.begin()+i+1, nums.end());
}

int main(){
    vector<int> nums = {1,1,5};
    // reverse(nums.begin()+1,nums.begin()+2+1);
    nextPermutation(nums);
    for(int i = 0;i<nums.size();i++){
        cout<<nums[i]<<"\t";
    }
    cout<<"\n";
}