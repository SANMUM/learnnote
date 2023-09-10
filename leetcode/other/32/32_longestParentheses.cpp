#include<iostream>
#include<stack>
#include<string>
using namespace std;
// int longestValidParentheses(string s) {
//     int n = s.length();
//     int ret = 0;
//     stack<int> st;
//     st.push(-1);
//     for (int i = 0; i < n; i++)
//     {
//         if(st.top() == -1 || s[st.top()] == ')'){
//             st.push(i);
//         }
//         else{
//             int j = st.top();
//             st.pop();
//             if(st.empty())
//                 st.push(i);
//             else{
//                 ret = max(ret,j+1);
//             }
            
//         }
//     }
//     return ret;
// }
int longestValidParentheses(string s) {
    int n = s.length();
    int ret = 0;
    stack<int> st;
    st.push(-1);
    for (int i = 0; i < n; i++)
    {
        if(s[i]=='('){
            st.push(i);
        }
        else{
            st.pop();
            if(st.empty()){
                st.push(i);
            }
            else{
                int j = st.top();
                ret = max(ret,i-j);
            }
        }
    }
    return ret;
}
int main(){
    // string  s = "()";
    string s =  ")(())";
    int res = longestValidParentheses(s);
    cout<<res<<endl;
}