#include <iostream>
#include <random>
#include <ctime>
#include <climits>
 
// 一些参数
const int MAX = 30;
const int LEN = 64;
 
void bucketSort(int arr[], int len);
void getRand(int arr[], int len, int min, int max);
 
int main() {
    int arr[LEN] = {0};
 
    // 产生随机值
    getRand(arr,LEN,0,MAX);
 
    // 打印随机值
    std::cout << "Before sorted:" << std::endl;
    for (int i : arr) {
        std::cout << i << " ";
    }
    std::cout << "" << std::endl;
 
    // 排序
    bucketSort(arr,LEN);
 
    // 打印输出值
    std::cout << "After sorted:" << std::endl;
    for (int i : arr) {
        std::cout << i << " ";
    }
}
 
void getRand(int arr[], int len, int min, int max) {
    std::default_random_engine e;
    e.seed(time(0));
    std::uniform_int_distribution<int> u(min,max);
    for (int i = 0; i < len; i++) arr[i] = u(e);
}
 
void bucketSort(int arr[], int len) {
    // 确定最大值和最小值
    int max = INT_MIN; int min = INT_MAX;
    for (int i = 0; i < len; i++) {
        if (arr[i] > max) max = arr[i];
        if (arr[i] < min) min = arr[i];
    }
 
    // 生成桶数组
    // 设置最小的值为索引0，每个桶间隔为1
    int bucketLen = max - min + 1;
    // 初始化桶
    int bucket[bucketLen];
    for (int i = 0; i < bucketLen; i++) bucket[i] = 0;
 
    // 放入桶中
    int index = 0;
    for (int i = 0; i < len; i++) {
        index = arr[i] - min;
        bucket[index] += 1;
    }
 
    // 替换原序列
    int start = 0;
    for (int i = 0; i < bucketLen; i++) {
        for (int j = start; j < start + bucket[i]; j++) {
            arr[j] = min + i;
        }
        start += bucket[i];
    }
}