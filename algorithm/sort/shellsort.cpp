#include<iostream>
#include<vector>
using namespace std;

void shellsort(vector<int> &nums,int N){
    for(int gap = N/2; gap>0; gap /=2){
        for(int i=gap;i<N;i++){
            for (int j = i; j-gap >=0 && nums[j-gap]>nums[j];j -= gap)
            {
                swap(nums[j-gap],nums[j]);
            }
            
        }
    }

}


int main()
{
    vector<int> nums = {100,33,3,7,11,6,8,5};
    int n = nums.size();
    shellsort(nums, n);
    for(int i=0; i<n; i++)
    {
        cout<<nums[i]<<" ";
    }
    printf("\n");
    return 0;
}
