#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<int> getvalue(int n){
        vector<int> ret;
        while (n !=0) {
            int val = n % 10;
            n = n / 10;
            ret.push_back(val);
        }
        return ret;
    }
    bool isHappy(int n) {
        unordered_set<int> nums_set;
        
        while (true)
        {
            
            vector<int> values = getvalue(n);
            int sum = 0;
            for(auto val: values) {
                sum += val* val;
                
            }
            cout<<sum<<endl;
            if(sum == 1){
                return true;
            }
            if(nums_set.find(sum) != nums_set.end()){
                return false;
            }
            else
            {
                nums_set.insert(sum);
            }
            
            n = sum;   
        }
    }
};

int main() {
    int n = 2;
    Solution ob;
    // vector<int> ret = ob.getvalue(n);
    bool res = ob.isHappy(n);
    cout<<boolalpha;
    cout<<res;
    // for(auto it : ret){
    //     cout << it <<"\t";
    // }
    cout<<endl;
}