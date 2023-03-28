/*
bubble algorithm description:
Compare adjacent elements,the first one is bigger than the second one,and switch places.
*/
#include<iostream>
#include<vector>
using namespace std;

void bubblesort(vector<int> &num, int n){
    if(n < 1) return ;
    bool is_swap;
    for(int i = 1;i< n;i++){
        is_swap = false;
        for(int j=1;j< n-i+1;j++){
            if(num[j-1] > num[j]){
                swap(num[j-1],num[j]);
                is_swap = true;
            }
        }

    if(!is_swap) break;
    }

}
int main(){
    vector<int> nums = {4,6,5,3,2,9};
    int len_num = nums.size();
    bubblesort(nums,len_num);
    cout<<"after sort is "<<endl;
    for(int i = 0;i<len_num ;i++){
        cout<<nums[i]<<endl;
    }


}