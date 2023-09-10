#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        int maxNum = n * n;
        vector<vector<int>> result(n, vector<int>(n, 0));
        int val = 1;
        int left = 0, top = 0;
        int right = n - 1, bottom = n - 1; 
        while (val <= maxNum) {
            // left -> right
            for (int i = left; i <= right; i++) {
                result[top][i] = val++;
            }
            top++;
            for (int i = top; i <= bottom; i++) {
                result[i][right] = val++;
            }
            right--;
            for (int i = right; i >= left; i--) {
                result[bottom][i] = val++;
            }
            bottom--;
            for (int i = bottom; i >= top; i--) {
                result[i][left] = val++;
            }
            left++;

        }
        return result;
    }
};

int main() {
    int n = 5;
    Solution ob;
    vector<vector<int>> ret = ob.generateMatrix(n);
    int len = ret.size();
    for(int i = 0; i < len; i++){
        for(auto it = ret[i].begin(); it!= ret[i].end();it++){
            std::cout << *it <<"\t";
        }
        std::cout << std::endl;
    }
}