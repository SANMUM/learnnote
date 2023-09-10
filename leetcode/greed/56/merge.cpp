#include <bits/stdc++.h>
using namespace std;
class Solution {
public:

    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> result;
        sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[0] < b[0];
        });
        result.push_back(intervals[0]);
        for (int i = 1; i < intervals.size(); i++) {
            if (intervals[i][0] <= result.back()[1]) {
                result.back()[1] = max(intervals[i][1],result.back()[1]);
            }
            else {
                result.push_back(intervals[i]);
            }
        }
        return result;
    }
};
int main() {
    vector<vector<int>> intervals = {{1,3},{2,6},{8,10},{15,18}};
    Solution ob;
    vector<vector<int>> ret = ob.merge(intervals);
    for (int i = 0; i < ret.size(); i++) {
        for (auto it : ret[i]) {
            cout << it << "\t";
        }
        cout << endl;
    }
}