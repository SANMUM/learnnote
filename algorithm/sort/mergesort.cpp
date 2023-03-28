
/*
quicksort algorithm description:
*/
#include<iostream>
#include<vector>

using namespace std;

void mergeCount(int a[], int L,int mid, int R){

    int *tmp  = new int[L+mid+R];
    int i = L;
    int j = mid + 1;
    int k=0;
    while (i<=mid && j<=R){
        if(a[i] < a[j])
            tmp[k++] = a[i++];
        else
            tmp[k++] = a[j++];
    }
    while (i<=mid)
    {
        tmp[k++] = a[i++];
    }
    while (j<=R)
    {
        tmp[k++] = a[j++];
    }
    for (size_t i = 0; i < k; i++)
    {
        a[L+i] = tmp[i];
    }
}

void mergesort(int a[],int L,int R){
    if(L>=R) return;
    int mid = L + (R-L)/2;
    mergesort(a,L,mid);
    mergesort(a,mid+1,R);
    mergeCount(a,L,mid,R);
}

int main() {
    
    int a[] = {0,34,66,2,5,95,4,46,27};
    mergesort(a, 0, sizeof(a)/sizeof(int));
    for(int i=0; i<=8; ++i) {
    std::cout<<a[i]<<" "; // print => 0 2 4 5 27 34 46 66 95
    }
    std::cout<<endl;
    return 0;
}