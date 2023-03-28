
/*
quicksort algorithm description:
*/
#include<iostream>
#include<vector>

using namespace std;

void quicksort(vector<int> &num,int l, int r){
    if(l + 1 >=r) return;
    int first=l,last = r-1,key=num[first];
    while(first<last){
        while (first<=last && num[last]>=key) last--;
        num[first]=num[last];
        while (first<=last && num[first]<=key) first++;
        num[last]=num[first];
    }
    num[first] = key;
    quicksort(num,l,first);
    quicksort(num,first+1,r);

}

int main(){
    vector<int> nums = {4,6,5,5,3,2,9};
    quicksort(nums,0,nums.size());
    int len_num = nums.size();
    cout<<"after sort is "<<endl;
    for(int i = 0;i<len_num ;i++){
        cout<<nums[i]<<endl;
    }
}