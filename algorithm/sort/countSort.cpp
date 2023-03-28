#include<iostream>
#include<cstring>
using namespace std;

int getMax(int a[],int N){
    int maxV = a[0];
    for (int i=1;i<N;i++){
        if(maxV<a[i]){
            maxV = a[i];
        }
    }
    return maxV;
}

void countSort(int a[],int N){
    int maxV = getMax(a,N);
    int maxn = 101;
    int count[maxn];
    int res[maxn];
    memset(count,0,sizeof(count));
    memset(res,0,sizeof(res));
    for(int i = 0; i<N; i++){
        count[a[i]]++;
    }
    for (int i = 1; i <= maxV; i++)
    {
        count[i] += count[i-1];
    }
    for (int  i = N-1; i >=0; --i)
    {
        int index = count[a[i]] - 1;
        res[index] = a[i];
        count[a[i]]--;
    }
    for(int i=0;i<N;++i){

        a[i] = res[i];
    }

    
}


int main(){
    int nums[] = {20,18,36,79,100,98};
    int N = sizeof(nums)/sizeof(int);
    countSort(nums, N);
    for(int i=0;i<N;i++){
        cout<<nums[i]<<" ";
    }
    cout<<endl;
}