#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int fib(int n) {
        if ( n < 2) return n;
        return fib(n-1) + fib(n-2);
    }
};

int main() {
    Solution ob;
    int ret = ob.fib(4);
    cout << ret << endl;
}