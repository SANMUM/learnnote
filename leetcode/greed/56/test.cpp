#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b){
            return a[0] < b[0];
        });
        vector<vector<int>> result;
        int l = intervals[0][0], r = intervals[0][1];
        for (int i = 1; i < intervals.size(); i++) {
            if (intervals[i][0] > r) {
                result.push_back({l, r});
                l = intervals[i][0];
                r = intervals[i][1];
            }
            else {
                r = max(r,intervals[i][1]);
            }
        }
        result.push_back({l,r});
        return result;
    }
};

int main(int argc, char const *argv[])
{
    Solution ob;
    vector<vector<int>> intervals = {{1,3},{2,6},{8,10},{15,18}};
    vector<vector<int>> ret = ob.merge(intervals);
    for (int i = 0; i < ret.size(); i++) {
        for (auto it : ret[i]) {
            cout << it << " ";
        }
    }
    cout << endl;
    return 0;
}
