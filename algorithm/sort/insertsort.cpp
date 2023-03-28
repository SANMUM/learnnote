/*
insertsort algorithm description:
The initial sorted interval has only one element, which is the first element in the array to go through the unsorted, 
and each element finds its place in the sorted interval and keeps the data in order
*/
#include<iostream>
#include<vector>

using namespace std;

void insertsort(vector<int> &nums, int N){
    if(N < 1) return ;
    for (size_t i = 0; i < N; i++)
    {
        /* code */
        for(int j=i;j > 0 && nums[j]< nums[j-1];j--){
            swap(nums[j],nums[j-1]);
        }
    }
    
}

int main(){
    vector<int> nums = {4,6,5,3,2,9};
    int len_num = nums.size();
    insertsort(nums,len_num);
    cout<<"after sort is "<<endl;
    for(int i = 0;i<len_num ;i++){
        cout<<nums[i]<<endl;
    }


}