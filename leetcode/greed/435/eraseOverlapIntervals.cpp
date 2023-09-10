#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        sort(intervals.begin(),intervals.end(),[](vector<int>& a, vector<int>& b) {
            return a[0] < b[0];
        });
        int count = 0;
        for (int i = 1; i < intervals.size(); i++) {
            if (intervals[i][0] > intervals[i-1][1]) {

            }
            else {
                intervals[i][1] =  min(intervals[i-1][1],intervals[i][1]);
                count++;
            }
        }
        return count
        ;
    }
};
int main() {

}