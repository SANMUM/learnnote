#include<iostream>
#include<string>
using namespace std;
// int myAtoi(string s) {
//     while(s!=""&&s[0]==' ') s.erase(0,1);
//     if(s=="") return 0;
//     bool negative=s[0]=='-'?true:false;
//     if(negative||s[0]=='+') s.erase(0,1);
//     if(s=="") return 0;
//     long long s_long=0;
//     for(auto it=s.begin();it!=s.end()&&(*it)-'0'>=0&&(*it)-'0'<=9;++it){
//         s_long*=10;
//         s_long+=(*(it)-'0');
//         if(s_long>(long long)INT32_MAX||s_long<(long long)INT32_MIN) return negative?INT32_MIN:INT32_MAX;
//     }
//     return negative?-s_long:s_long;
// }

// int myAtoi(string s) {
//     int i=0;
//     int len = s.length();
//     bool flag = true;
//     long long sum = 0;
//     while (s[i] == ' ') i++;
//     while (s[i]=='+' || s[i]=='-')
//     {
//         if(s[i] == '-')
//             flag = false;
//         if(s[i+1] == '-' && s[i]=='+'){
//             return 0;
//         }
//         if(s[i+1] == '+' &&s[i]=='-'){
//             return 0;
//         }
//         if(s[i+1]== '+' && s[i]=='+'){
//             return 0;
//         }
//         if(s[i+1] == '-' && s[i]=='-'){
//             return 0;
//         }
//         i++;
//     }
//     while (s[i] >= '0' && s[i] <= '9')
//     {
//         sum += (s[i] - '0');
//         if(sum >= INT32_MAX && flag)
//         {
//             return INT32_MAX;
//         }
//         if((0-sum) <= INT32_MIN)
//         {
//             return INT32_MIN;
//         }
//         if(s[i+1]>= '0' && s[i+1]<= '9')
//         {
//             sum *= 10;
//         }
//         i++;
//     }
//     if(!flag){
//         return -sum;
//     }
//     else{
//         return sum;
//     } 
// }
#define INT_MAX INT32_MAX
#define INT_MIN INT32_MIN
int myAtoi(string s) {
	int result = 0;
	int sign = 1;//记录正负号
	int index = 0;

	//1.去掉空格
	while (index < s.size() && ' ' == s[index])index++;
	//2.记录正负号（如果有的话）
	if (index < s.size() && '-' == s[index]) { sign = -1; index++; }
	else if (index < s.size() && '+' == s[index])index++;

	//3.处理数字
    printf("%d \n",index);
	while (index < s.size() && s[index] >= '0' && s[index] <= '9') {
		int num = s[index] - '0';
		if (result > (INT_MAX - num) / 10)return INT_MAX;//超出最大值边界返回最大值,减去num的作用是防止加上num后超出边界。
		if (result < (INT_MIN + num) / 10) return INT_MIN;//超出最小值边界返回最小值，负数需要加上num，作用同上
		result = result * 10 + sign * num;
		index++;
	}
	return result;
}

int main(){
    // string s = "4193 with words";
    // string s = "-91283472332";
    // string s = "-13+8";
    string s = "+-13";
    int ret = myAtoi(s);
    printf("s = %d\n",ret);

}