#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> result;        
        int top = 0, left = 0;
        int bottom = matrix.size() - 1, right = matrix[0].size() - 1;
        int count = (bottom + 1) * (right + 1);
        while (count>=1) {
            for (int i = left; i <= right && count>=1; i++) {
                result.push_back(matrix[top][i]);
                count--;
            }
            top++;
            for (int i = top; i <= bottom  && count>=1; i++) {
                result.push_back(matrix[i][right]);
                count--;
            }
            right--;
            for (int i = right; i>= left  && count>=1; i--) {
                result.push_back(matrix[bottom][i]);
                count--;
            }
            bottom--;
            for (int i = bottom; i>= top  && count>=1; i--) {
                result.push_back(matrix[i][left]);
                count--;
            }
            left++;
               
        }
        
        return result;
    }
};

int main() {
    Solution ob;
    vector<vector<int>> nums = {{1,2,3,4},{5,6,7,8},{9,10,11,12}};
    vector<int> ret = ob.spiralOrder(nums);
    for (auto it : ret) {
        cout << it  << " ";
    }
    cout << endl;
}