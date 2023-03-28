#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
void bucketSort(vector<int> &nums){
    if(nums.empty()) return;
    int low = *min_element(nums.begin(),nums.end());
    int high = *max_element(nums.begin(),nums.end());
    int n = high - low +1;
    vector<int> buckets(n);
    vector<int> res;
    for(auto x : nums) ++buckets[x-low];
    for (int i = 0; i < n ; i++)
    {
        for (int j = 0; j < buckets[i]; j++)
        {
            res.push_back(i+low);
        }
        
        
    }
    int N = nums.size();
    for (int i = 0; i < N; i++)
    {
        cout<<res[i]<<" ";
    }
    cout<<endl;
    
}

int main(){
    vector<int> nums = {4,6,5,3,2,9};
    bucketSort(nums);
    
    
}