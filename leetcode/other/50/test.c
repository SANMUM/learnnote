// #include<iostream>
#include<stdio.h>
// using namespace std;
#include <stdlib.h>
#include<stdint.h>

int main(){
    int a = 4.2;
    // char s[32]={};
    // itoa(a,s,2);

    // float b = a;
    float b = *(float *)&a;
    

    // cout<<"a = " << a << " b = "<<b<<endl;
    // printf("%d\t",a);
    // printf("%lf\t",a);

    printf("%p\n",&a);
    printf("%p\n", b);
    // printf("%x\n",a);
    // printf("%f\n", *b);
}