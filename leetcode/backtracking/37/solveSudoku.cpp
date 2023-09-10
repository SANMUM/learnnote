#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool backtracking(vector<vector<char>>& board) {
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board.size(); j++) {
                if (board[i][j] != '.') continue;
                for (int k = '1'; k <= '9'; k++) {
                    if (isValid(i,j,k,board)) {
                        board[i][j] = k;
                        if (backtracking(board)) return true;
                        board[i][j] = '.';
                    }
                }
                return false;
            }
        }
        return true;
    }
    void solveSudoku(vector<vector<char>>& board) {
        backtracking(board);
    }
    bool isValid(int i, int j, char k, vector<vector<char>>& board) {
        // 查询i行是否有重复
        for (int col = 0; col < 9; col++) {
            if (board[i][col] == k) {
                return false;
            }
        }
        // 查询j列是否有重复
        for (int row = 0; row < 9; row++) {
            if (board[row][j] == k) {
                return false;
            }
        }
        // 查询 单元格内是否有重复
        int startrow = (i / 3) * 3;
        int startcol = (j / 3) * 3;
        for (int li = startrow; li < startrow + 3; li++) {
            for (int lj = startcol; lj <  startcol + 3; lj++) {
                if (board[li][lj] == k) {
                    return false;
                }
            } 
        }
        return true;
    }
};
int main() {

}