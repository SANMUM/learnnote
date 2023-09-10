#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void backtracking(vector<string>& checkboard, int row, int n) {
        if (row == n ) {
            ret.push_back(checkboard);
            return;
        }
        for (int col = 0; col < n; col++) {
            if (isValid(checkboard, row, col, n)) {
                checkboard[row][col] = 'Q';
                backtracking(checkboard,row+1, n);
                checkboard[row][col] = '.';
            }
        }
    }
    vector<vector<string>> solveNQueens(int n) {
        vector<string> checkboard(n, ::string(n,'.'));
        backtracking(checkboard,0, n);
        return ret;

    }
    bool isValid(vector<string>& checkboard, int row, int col, int n) {
        // 排查列
        for (int i = 0; i < row; i++) {
            if (checkboard[i][col] == 'Q') {
                return false;
            }
        }
        // 45度角
        for (int i = row-1, j = col-1; i >=0 && j>=0 ; i--,j--) {
            if (checkboard[i][j] == 'Q') {
                return false;
            }
        }
        // 135度角
        for (int i = row-1, j = col+1; i>=0&&j < n; i--, j++) {
            if (checkboard[i][j] == 'Q') {
                return false;
            }
        }
        return true;
    }
private:
    vector<vector<string>> ret;
    vector<string> path;
};
int main() {
    int n = 4;
    Solution ob;
    vector<vector<string>> ret = ob.solveNQueens(n);
    for (int i = 0; i < ret.size(); i++) {
        for (auto it : ret[i]) {
            ::cout << it << "\t";
        }
        ::cout << ::endl; 
    }
}