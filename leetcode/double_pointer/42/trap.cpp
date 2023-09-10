#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int trap(vector<int>& height) {
        if (height.size() <= 2) return 0;
        stack<int> st;
        st.push(0);
        int sum = 0;
       
        for (int i = 1; i < height.size(); i++) {
            if (height[i] < height[st.top()]) {
                st.push(i);
            }
            if (height[i] == height[st.top()]) {
                st.pop();
                st.push(i);
            }
            else {
                while (!st.empty() && height[i] > height[st.top()]) {
                    int mid = st.top();
                    st.pop();
                    if (!st.empty()) {
                        int h = min(height[st.top()],height[i]) - height[mid];
                        int w = i - st.top() - 1;
                        sum +=  h * w;
                    }
                }
                st.push(i);
            }
        }
        return sum;
    }
};

int main() {

}