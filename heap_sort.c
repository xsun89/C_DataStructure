//
// Created by Xin Sun on 2020-12-05.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#define swap(a,b){\
    __typeof(a) __tmp = a;\
    a = b; \
    b = __tmp;\
}
void downUpdate(int *arr, int n, int ind)
{
    while (ind << 1 <= n){
        int tmp = ind, l = ind << 1, r = ind << 1 | 1;
        if(arr[l] > arr[tmp] ) tmp = l;
        if(r <= n && arr[r] > arr[tmp]) tmp = r;
        if(tmp == ind) break;

        swap(arr[tmp], arr[ind]);
        ind = tmp;
    }
}

void heapSort(int *arr, int n)
{
    arr -= 1;//arr[1] can get arr[0]
    for (int i = n >> 1 ; i >= 1; i--){
        downUpdate(arr, n, i);
    }

    for(int i=n; i>=1; i--){
        swap(arr[i], arr[1]);
        downUpdate(arr, i-1, 1);
    }
}
void output(int *arr, int n)
{
    printf("[");
    for(int i=0; i<n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("]\n");
}
int main()
{

    srand(time(0));
#define max_n 20
    int *arr = (int *)malloc(sizeof(int)*max_n);
    for(int i = 0; i < max_n; i++){
        arr[i] = rand() % 100;
    }
    output(arr, max_n);
    heapSort(arr, max_n);
    output(arr, max_n);
    free(arr);
#undef max_n
    return 0;
}
