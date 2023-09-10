#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int trap(vector<int>& height) {
        if (height.empty()) return 0;
        stack<int> st;
        st.push(0);
        int sum = 0;
        for (int i = 1; i < height.size(); i++) {
            if (height[i] < height[st.top()]) {
                st.push(i);
            }
            else if (height[i] == height[st.top()]){
                st.pop();
                st.push(i);
            }
            else {
                while(!st.empty() && height[i] > height[st.top()]) {
                    int mid = st.top();
                    st.pop();
                    if (!st.empty()) {
                        int h = min(height[i], height[st.top()]) - height[mid];
                        int width = i - st.top() - 1;
                        sum += h * width; 
                    }
                }
                st.push(i);
            }
        }
        return sum;
    }
};

int main() {
    vector<int> height = {0,1,0,2,1,0,1,3,2,1,2,1};
    Solution ob;
    int ret = ob.trap(height);
    cout << ret << endl;

}