// #include<iostream>
#include<stdio.h>
// using namespace std;
#include <stdlib.h>
#include<stdint.h>

int main(){
    int a = 4;
    // int c = 5;
    
    // char s[32]={};
    // itoa(a,s,2);

    // float b = a;
    float b = *(float *)&a;
    float c = 18165465.1;
    float d = 1848678.1;

    // cout<<"a = " << a << " b = "<<b<<endl;
    // printf("%x\n",a);
    // printf("%lf\t",a);

    // printf("%p\n",&a);
    // printf("%p\n",&c);
    // printf("%p\n", &b);

    // printf("%x\n",a);
    // printf("%x\n", b);
    // printf("%x\n",c);
    // printf("%x\n",d);
    }