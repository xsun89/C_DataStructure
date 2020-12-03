//
// Created by Xin Sun on 2020-12-02.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_N 20
#define TEST(arr, n, func, args...){ \
    int *tmp = (int *)malloc(sizeof(int)*n); \
    memcpy(tmp, arr, sizeof(int)*n); \
    printf("%s\n", #func);           \
    func(args);                      \
    output(num, n);                                 \
    free(tmp); \
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
    for (int i =0; i<n; i++){
        int min = data[i];
        int p = i;
        for (int j = i+1; j<n; j++){
            if(data[j] < min){
                min = data[j];
                p = j;
            }
        }
        swap(data[p], data[i]);
    }
}
int main()
{
    srand(time(0));

    int num[MAX_N];
    for (int i = 0; i <MAX_N; i++){
        num[i] = rand()%100;
    }
    output(num, MAX_N);

    //insert_sort(num, 10);
    //bubble_sort(num, 20);
    TEST(num, MAX_N, bubble_sort, num, MAX_N);
    TEST(num, MAX_N, insert_sort, num, MAX_N);
    TEST(num, MAX_N, select_sort, num, MAX_N);
    TEST(num, MAX_N, merge_sort, num, 0, MAX_N-1);
    //merge_sort(num, 0, 19);

    return 0;
}