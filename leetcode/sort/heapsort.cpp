#include <bits/stdc++.h>
using namespace std;
class Solution{
public:
    
    void max_heapify(vector<int>& nums, int start, int end) {
        int dad = start;
        int son = dad*2 + 1;
        //若子节点指标在范围内才做比较
        while (son <= end) {
            //先比较两个子节点大小，选择最大的
            if (son + 1 <= end && nums[son] < nums[son+1]) {
                son++;
            }
            //如果父节点大于子节点代表调整完毕，直接跳出函数
            if (nums[dad]> nums[son]) {
                return;
            }
            //否则交换父子内容再继续子节点和孙节点比较
            else {
                swap(nums[dad], nums[son]);
                dad = son;
                son = dad*2 + 1;
            }
        }
    }
   
    void heap_sort(vector<int>& nums) {
        int len = nums.size();
        for (int i = len/2 - 1; i >= 0; i--) {
            max_heapify(nums,i,len-1);
        }
        for (int i = len -1; i > 0; i--) {
            swap(nums[0], nums[i]);
            max_heapify(nums,0,i-1);
        }
    }

};

int main() {
    vector<int> nums = {34,66,2,5,95,4,46,27};
    Solution ob;
    // ob.heap_sort(nums,sizeof(nums)/sizeof(int));
    ob.heap_sort(nums);
    for (auto it: nums) {
        cout << it << "\t";
    }
    cout << endl;
}