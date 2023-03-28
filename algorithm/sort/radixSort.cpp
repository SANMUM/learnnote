#include<iostream>
using namespace std;

int maxdigit(int a[],int N){
    int maxV = a[0];
    for(int i = 1;i<N;i++){
        if(a[i]>maxV){
            maxV = a[i];
        }
    }
    int d = 1;
    int p = 10;
    while (maxV>=p)
    {
        maxV /= 10;
        d++;
    }
    
    return d;
}
void radixsort(int data[], int n) //基数排序
{
    int d = maxdigit(data, n);
    int *tmp = new int[n];
    int *count = new int[10]; //计数器
    int i, j, k;
    int radix = 1;
    /* core algorithm */
    for(i = 1; i <= d; i++) //进行d次排序
    {
        for(j = 0; j < 10; j++)
            count[j] = 0; //每次分配前清空计数器
        for(j = 0; j < n; j++)
        {
            k = (data[j] / radix) % 10; //统计每个桶中的记录数
            count[k]++;
        }
        for(j = 1; j < 10; j++)
            count[j] = count[j - 1] + count[j]; //将tmp中的位置依次分配给每个桶,
        for(j = n - 1; j >= 0; j--) //将所有桶中记录依次收集到tmp中
        {
            k = (data[j] / radix) % 10;
            tmp[count[k] - 1] = data[j];  //reversely pop in buck
            count[k]--;
        }
        for(j = 0; j < n; j++) //将临时数组的内容复制到data中
            data[j] = tmp[j];
        radix = radix * 10;
    
    }
    delete []tmp;
    delete []count;
}
int main(){
    int nums[] = {20,18,36,79,100,98};
    int N = sizeof(nums)/sizeof(int);
    radixsort(nums, N);
    for(int i=0;i<N;i++){
        cout<<nums[i]<<" ";
    }
    cout<<endl;
    // int res = maxdigit(nums,N);
    // cout<<res<<endl;
}