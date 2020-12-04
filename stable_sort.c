//
// Created by Xin Sun on 2020-12-02.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_N 20
#define TEST(num, n, func, args...){ \
    int *arr = (int *)malloc(sizeof(int)*n); \
    memcpy(arr, num, sizeof(int)*n); \
    printf("%s\n", #func);           \
    output(arr, n);                  \
    func(args);                      \
    output(arr, n);                                 \
    free(arr); \
}
#define swap(a, b) { \
    __typeof(a) tmp = a;  \
         a = b;      \
         b = tmp;     \
}
void insert_sort(int *data, int n)
{
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j>0; j--){
            if(data[j] < data[j-1]){
                swap(data[j], data[j-1]);
            }
        }
    }

    return;
}

void bubble_sort(int *data, int n)
{
    for(int i=n-1; i>0; i--){
        for(int j=0; j<i; j++)
        {
            if(data[j] > data[j+1])
            {
                swap(data[j], data[j+1]);
            }
        }
    }

    return;
}

void merge_sort(int *data, int l, int r)
{
    if(r - l <= 1){
        if(r - l == 1 && data[r] < data[l]){
            swap(data[r], data[l]);
        }
        return;
    }
    int mid = (r+l) >> 1;
    merge_sort(data, l, mid);
    merge_sort(data, mid+1, r);
    int p1 = l, p2 = mid +1, p = 0;
    int *tmp = (int *)malloc(sizeof(int)*(r-l+1));
    while(p1 <= mid || p2 <= r) {
        if(p2 > r || (p1 <= mid && data[p1] < data[p2])) {
            tmp[p++] = data[p1++];
        }else{
            tmp[p++] = data[p2++];
        }
    }
    memcpy(data+l, tmp, sizeof(int)*(r-l+1));
    free(tmp);

    return;
}

void output(int *data, int n)
{
    printf("[");
    for (int i = 0; i <n; i++) {
        printf("%d ", data[i]);
    }
    printf("]\n");
}

void select_sort(int *data, int n)
{
    for (int i =0; i<n-1; i++){
        int p = i;
        for (int j = i+1; j<n; j++){
            if(data[j] < data[p]){
                p = j;
            }
        }
        swap(data[p], data[i]);
    }
}
/*
 * 【基准值、partition】
拿出第1个元素作为基准值
【尾指针】先从后往前找小于基准值的元素，放到第1个元素位置(已为空)，【头指针】再从前往后找大于基准值的值，放到刚刚空出的位置，循环
最后头尾指针重合，指向一个空位置，放入基准值
再对基准值左右两部分分别进行以上操作
 */
void quick_sort(int *data, int l, int r)
{
    if(l > r){
        return;
    }
    int x = l, y = r, z = data[l];
    while(x < y){
        while(x < y && data[y] > z) y--;
        if(x < y){
            data[x++] = data[y];
        }
        while(x < y && data[x] < z) x++;
        if(x < y){
            data[y--] = data[x];
        }
    }
    data[x] = z;
    quick_sort(data, l, x-1);
    quick_sort(data, x+1, r);
    return;
}

void enhanced_quick_sort(int *data, int l, int r)
{
    while(l < r){
        int x = l, y = r, z = data[(l+r)>>1];
        do {
            while (x <= y && data[y] > z) y--;
            while (x <= y && data[x] < z) x++;
            if (x <= y) {
                swap(data[x], data[y]);
                x++;
                y--;
            }
        }while(x <= y);
        enhanced_quick_sort(data, x, r); //x will be y+1, y+1 -> r range has been sorted already
        r = y; //move r to be y, since y+1 -> r already sorted.
    }
    return;
}
int main()
{
    srand(time(0));

    int num[MAX_N];
    for (int i = 0; i <MAX_N; i++){
        num[i] = rand()%100;
    }
    //output(num, MAX_N);

    //insert_sort(num, 10);
    //bubble_sort(num, 20);
    TEST(num, MAX_N, bubble_sort, arr, MAX_N);
    TEST(num, MAX_N, insert_sort, arr, MAX_N);
    TEST(num, MAX_N, select_sort, arr, MAX_N);
    TEST(num, MAX_N, merge_sort, arr, 0, MAX_N-1);
    TEST(num, MAX_N, quick_sort, arr, 0, MAX_N-1);
    TEST(num, MAX_N, enhanced_quick_sort, arr, 0, MAX_N-1);
    //merge_sort(num, 0, 19);

    return 0;
}