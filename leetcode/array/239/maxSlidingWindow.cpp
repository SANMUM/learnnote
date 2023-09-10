#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> result;
        priority_queue<pair<int, int>> p_que;
        for (int i = 0; i < k; i++) {
            p_que.emplace(nums[i], i);
        }
        result.push_back(p_que.top().first);
        for (int i = k; i < nums.size(); i++) {
            p_que.emplace(nums[i], i);
            while (p_que.top().second <= i -k) {
                p_que.pop();
            }
            result.push_back(p_que.top().first);
        }
        return result;
    }
};

int main() {
    Solution ob;
    vector<int> nums = {1,3,-1,-3,5,3,6,7};
    int k = 3;
    vector<int> ret = ob.maxSlidingWindow(nums, k);
    for (auto it : ret) {
        cout << it << " ";
    }
    cout << endl;
}