/*
SelectSort algorithm descriptions:
Sorted interval and unsorted interval. 
Each time it finds the smallest element in the unsorted interval and puts it at the end of the sorted interval
*/
#include<iostream>
#include<vector>
using namespace std;

void SelectSort(vector<int> &num,int n){
    if(n<=1) return;
    int mid;
    for (int i=0; i< n ;i++){
        mid = i;
        for(int j=i+1;j<n-1;j++){
            if(num[j]<num[mid]){
                mid = j;
            }
        }
        swap(num[i],num[mid]);
    }
}

int main(){
    vector<int> nums = {4,6,5,3,2,9};
    int len_num = nums.size();
    SelectSort(nums,len_num);
    cout<<"after sort is "<<endl;
    for(int i = 0;i<len_num ;i++){
        cout<<nums[i]<<endl;
    }

}