#include<iostream>
#include<vector>
using namespace std;
int binarySearch(vector<int>& nums,int target){
    int left = 0, right = nums.size()-1;
    while(left <= right){
        int mid = (left + right)/2;
        if(nums[mid] < target){
            left = mid+1;
        }
        else{
            right = mid - 1;
        }
    }
    return right+1;
}
vector<int> searchRange(vector<int>& nums, int target) {
    vector<int> ret;
    int left = binarySearch(nums,target);
    int right = binarySearch(nums,target+1)-1;
    // cout<<left<<"\t"<<right;
    if(left<= right){
        ret.push_back(left);
        ret.push_back(right);
    }
    else{
        ret.push_back(-1);
        ret.push_back(-1);
    }
    return ret;
}

int main(){
    // vector<int> nums = {5,7,7,8,8,10};
    vector<int> nums = {5,7,7,8,8,10};
    int target = 6;
    vector<int> res = searchRange(nums,target);
    for(auto it = res.begin();it != res.end();it++){
        cout<<*it<<"\t";
    }
    // int ret = binarySearch(nums,target);
    // cout<<ret;
    cout<<endl;
}