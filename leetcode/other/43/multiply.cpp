// #include<iostream>
#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    string multiply(string num1, string num2) {
        if(num1 == "0" || num2 == "0")
        return "0";
        int size_1 = num1.size();
        int size_2 = num2.size();
        string ret(size_1 + size_2,'0');
        for(int i = size_1 - 1; i >= 0; i--){
            for(int j = size_2 - 1; j >= 0;j--){
                int num = (ret[i+j+1]-'0') + (num1[i] - '0')*(num2[j]-'0');
                ret[i+j+1] = num % 10 + '0';
                ret[i+j] += num/10;
            }
        }
        int k = 0;
        for ( k = 0; k <size_1+size_2; k++)
        {
            if( ret[k] != '0')
             break;   
            
        }

        cout<<ret.substr(k);
        return ret.substr(k);
        
    }
};

int main(){
    string nums1 = "123",nums2 = "111";
    Solution ob;
    ob.multiply(nums1,nums2);
    
    cout<<endl;

}