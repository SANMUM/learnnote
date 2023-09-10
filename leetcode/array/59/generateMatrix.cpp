#include<bits/stdc++.h>
using namespace std;
// class Solution {
// public:
//     vector<vector<int>> generateMatrix(int n) {
//         vector<vector<int>> ret(n,vector<int>(n,0));
//         int value = 1;
//         for (int L = n; L > 0; L -= 2) {
//             int row = (n - L) / 2;
//             int col = row;
//             for(int k = 0; k < L-1; k++){
//                 int curr = row;
//                 int curc = col + k;
//                 ret[curr][curc] = value;
//                 for(int k = 0; k < 3; k++){
//                     value += n - 1;
//                     int nextr = curc;
//                     int nextc = n - 1 - curr;
//                     ret[nextr][nextc] = value ;
//                     curc = nextc;
//                     curr = nextr;
//                 }
//                 value -= (n-1)*3 - 1;
//                 // std::cout << value <<endl;
//                 // break;
//             }
//             value = n + (n-1) * 3 ;
            
//         }
//         return ret;
//     }
// };

class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> ret(n,vector<int>(n,0));
        int maxNum = n * n;
        int num = 1;
        int left = 0, top = 0, right = n - 1, bottom = n - 1;
        while (num <= maxNum) {
            // from left to right
            for(int i = left; i <= right; i++) ret[top][i] = num++;
            top++;
            // from top to bottom
            for(int i = top; i <= bottom; i++) ret[i][right] = num++;
            right--;
            // from right to left
            for(int i = right; i>= left; i--) ret[bottom][i] = num++;
            bottom--;
            // from bottom to top
            for(int i = bottom;i>= top; i--) ret[i][left] = num++;
            left++;
        }
        return ret;
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