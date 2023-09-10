#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    double quickmutil(double x, long n){
        if( n == 0){
            return 1.0;
        }
        double ret = quickmutil(x,n/2);
        return n % 2 == 0 ?  ret* ret: ret*ret*x;
    }
    double myPow(double x, int n) {
        long d = n;
        return d > 0 ?  quickmutil(x,d) : 1/quickmutil(x,-d);
    }
};

class Solution2 {
public:
    double quickMul(double x, long long N) {
        double ans = 1.0;
        // 贡献的初始值为 x
        double x_contribute = x;
        // 在对 N 进行二进制拆分的同时计算答案
        while (N > 0) {
            if (N % 2 == 1) {
                // 如果 N 二进制表示的最低位为 1，那么需要计入贡献
                ans *= x_contribute;
            }
            // 将贡献不断地平方
            x_contribute *= x_contribute;
            // 舍弃 N 二进制表示的最低位，这样我们每次只要判断最低位即可
            N /= 2;
        }
        return ans;
    }

    double myPow(double x, int n) {
        long long N = n;
        return N >= 0 ? quickMul(x, N) : 1.0 / quickMul(x, -N);
    }
};

int main(){
    Solution ob;
    double x = 2.00000;
    int n = -2;
    double ret = ob.myPow(x,n);
    cout<<ret;
    cout<<endl;
}