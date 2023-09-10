#include<bits/stdc++.h>
using namespace std;
// class Solution {
// public:
//     void rotate(vector<vector<int>>& matrix) {
//         int n = matrix.size();
//         for (int row = 0; row < (n / 2); row++) {
//             for (int col = 0; col < (n+1)/ 2; col++) {
//                 int temp = matrix[row][col];
//                 matrix[row][col] = 
//             }
            
            
//         }
//     }
// };

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        for (int L = n; L > 0; L -=2) {
            int row = (n-L) / 2;
            int col =  row;
            for (int j = 0; j < L - 1; j++) {
                int r = row, c = col + j;
                int temp = matrix[r][c];
                for (int k = 0; k < 4; k++) {
                    int cc = n - 1 - r;
                    int rr = c;
                    swap(matrix[rr][cc], temp);
                    r = rr;
                    c = cc;
                }
            }
        }
        
    }
};

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        for (int row = 0; row < n/2; row++) {
            for (int col = row; col < n - row - 1; col++) {
                int temp = matrix[row][col];
                matrix[row][col] = matrix[n-col-1][row];
                matrix[n-col-1][row] = matrix[n-row-1][n-col-1];
                matrix[n-row-1][n-col-1] = matrix[col][n-1-row];
                matrix[col][n-1-row] = temp;
            }
        }
    }
};
int main(int argc, char const *argv[])
{
    Solution ob;
    vector<vector<int>> matrix = {{1,2,3},{4,5,6},{7,8,9}};

    ob.rotate(matrix);
    for (int i = 0; i < matrix.size(); i++) {
        for (auto it : matrix[i]) {
            cout << it << " ";
        }
        cout << endl;
    }
    return 0;
}
