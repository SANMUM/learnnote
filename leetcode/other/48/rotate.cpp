#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
         int n = matrix.size();
         for (int L = n; L > 0; L -= 2)
         {
            
            int row = (n-L)/2;
            int col = row;
            
            // cout<<temp<<"\t";
            // cout<<"wai ";
            // cout<<row<<"\t";
            for(int k=0;k < L-1; k++){
                int curr = row;
                int curc = col + k;
                // cout<<"row "<<curr<<" curc "<<curc<<endl;
                // cout<<matrix[curr][curc]<<"\t";
                int temp = matrix[curr][curc];
                
                for (int i = 0; i < 4; i++)
                {
                    int nextr = curc;
                    int nextc = n-1-curr;
                    swap(temp,matrix[nextr][nextc]);
                    curc = nextc;
                    curr = nextr;
                }
                
            }
         }
                
    }
};

int main(){
    // vector<vector<int>> matrix = {{1,2,3},{4,5,6},{7,8,9}};
    vector<vector<int>> matrix = {{5,1,9,11},{2,4,8,10},{13,3,6,7},{15,14,12,16}};
    Solution ob;
    ob.rotate(matrix);
    for(int i=0;i<matrix.size();i++){
        for(auto it = matrix[i].begin();it != matrix[i].end();it++){
            cout<<*it<<"\t";
        }
        cout<<endl;
    }
}