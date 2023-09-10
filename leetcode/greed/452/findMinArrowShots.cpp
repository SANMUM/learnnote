#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        sort(points.begin(), points.end(), [](vector<int>& a, vector<int>& b){
            return a[0] <  b[0];
        });
        int result = 1;
        for (int i = 1; i < points.size(); i++) {
            if (points[i][0] > points[i-1][1]) {
                result++;
            }
            else {
                points[i][1] = min(points[i-1][1],points[i][1]);
            }
        }
        return result;
    }
};
int main() {
    
}