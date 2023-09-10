class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        for (int i = 0; i < matrix.size(); i++) {
            for (auto it : matrix[i]) {
            if (it ==  target) {
                return true;
            }
        }
        }
        
        return false;
    }
};