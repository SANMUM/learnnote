#include<iostream>
using namespace std;

// int divide(int dividend, int divisor) {
//     if(1 == divisor) return dividend;
//     if(-1 == divisor) {
//         if(dividend <= INT32_MIN)
//         return INT32_MAX;
//         else if(dividend > INT32_MAX){
//             return INT32_MIN;
//         }
//         else{
//             return -dividend;
//         }
//     }
//     int count = 0;
//     int sign = 1;
//     if((dividend>0 && divisor<0) ||(dividend<0 && divisor>0) ){
//         sign = -1;
//     }
//     unsigned int a = 0;
//     unsigned int b = 0;
//     if(dividend == INT32_MIN){
//         a = (unsigned int) dividend;
        
//     }
//     if(divisor == INT32_MIN){
//         b = (unsigned int ) divisor;
//     }
//     a = dividend > 0 ?  dividend : -dividend;
//     b = divisor > 0 ?  divisor :  -divisor;
//     // cout<<a;
//     // cout<<b;
//     // cout<<endl;
//     // return 1;
//     while(true){
//         if(a < b) break;
//         else
//         {
//             a -= b;
//             count++;
//         }
//     }

//     return sign > 0 ? count : -count;
// }

int divide(int dividend,int divisor){
    if(dividend == INT32_MIN && divisor == -1) return INT32_MAX;
    int sign = (dividend > 0) ^ ( divisor > 0) ? -1 : 1;
    int LIMIT = -107374182;
    if(dividend>0){
        dividend = -dividend;

    }
    if(divisor>0){
        divisor = -divisor;
    }

    unsigned int count = 0;
    while(dividend<= divisor){
        int c = divisor,d = -1;
        while(c >= LIMIT && d >= LIMIT && c>= dividend-c){
            c += c;
            d += d;
        }
        dividend -= c;
        count += d;
    }
    return sign > 0 ? -count:count;
}
int main(){
    // int dividend = 10,divisor = 3;
    // int dividend = -7,divisor = -3;
    int dividend = -2147483648,divisor=2;
    int ret = divide(dividend,divisor);
    cout<<ret<<endl;

}