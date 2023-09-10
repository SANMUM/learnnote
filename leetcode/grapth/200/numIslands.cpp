#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    void dfs(vector<vector<char>>& grid, int row, int col) {
        int row_len = grid.size();
        int col_len = grid[0].size();
        grid[row][col] = '0';
        if (row-1 >=0 && grid[row-1][col] == '1') dfs(grid, row-1, col);
        if (row+1 < row_len && grid[row+1][col] == '1') dfs(grid, row+1, col);
        if (col-1 >= 0 && grid[row][col-1] == '1') dfs(grid, row, col - 1);
        if (col+1 < col_len && grid[row][col+1] == '1') dfs(grid, row, col+1); 
    }
    int numIslands(vector<vector<char>>& grid) {
        int row_n = grid.size();
        int col_n = grid[0].size();
        int count = 0;
        for (int row = 0; row < row_n; row++) {
            for (int col = 0; col < col_n; col++) {
                if (grid[row][col] == '1') {
                    count++;
                    dfs(grid, row, col);
                }
            }
        }
        return count;
    }
};
int main() {
    Solution ob;
    vector<vector<char>> grid = {
  {'1','1','1','1','0'},
  {'1','1','0','1','0'},
  {'1','1','0','0','0'},
  {'0','0','0','0','0'}
  };
  int result = ob.numIslands(grid);
  cout << result << endl;
}