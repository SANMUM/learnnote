#include<iostream>
bool isPalindrome(int x) 
{
    if(x < 0)
        return false;
    int revers = 0;
    int lx = 0;
    int raw = x;
    while(x != 0)
    {
        lx = x % 10;
        revers  = revers*10 + lx;
        x = x /10;
    }
    
    std::cout<<revers<<std::endl;
    return (revers == raw) ? true:false;
}


int main(){
    int input = 141;
    bool ret = isPalindrome(input);
    // std::cout<<ret<<std::endl;
}