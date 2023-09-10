#include<iostream>
#include<unordered_map>
using namespace std;

string intToRoman(int num) {
    int value[] = {1000,900,500,400,100,90,50,40,10,9,5,4,1};
    string symbol[] = {"M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I"};
    
    string roman;
    int len = sizeof(value)/sizeof(int);
    for (int  i = 0; i<len; i++)
    {
        while(value[i]<= num){
            num-= value[i];
            cout<<num<<endl;
            roman+=symbol[i];
        }
        if(num == 0){
            break;
        }
    
    }
    
    return roman;
    
}
int main(){
    int num = 1994;
    string res = intToRoman(num);
    cout<<res<<endl;
}