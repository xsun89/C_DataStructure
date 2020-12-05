//
// Created by Xin Sun on 2020-12-04.
//
#include <stdio.h>
#include <stdlib.h>

#define P(func) printf("%s-%d\n", #func, func);
//1,3,5,7,9,11
int binarySearch(int *num, int n, int x)
{
    int mid;
    int head = 0, tail = n - 1;
    while (head <= tail)
    {
        mid = (tail + head) >> 1;
        if(num[mid] == x) {
            return mid;
        }else if(num[mid] > x){
            tail = mid - 1;
        }else{
            head = mid + 1;
        }

    }

    return -1;
}

//111111111000000 find last 1
int binarySearch1(int *num, int n)
{
    int mid;
    int head = -1, tail = n - 1;
    while (head < tail)
    {
        mid = (tail + head + 1) >> 1;
        if(num[mid] == 1) {
            head = mid;
        }else{
            tail = mid - 1;
        }
    }

    return head;
}

//000000111111111 find first 1
int binarySearch2(int *num, int n)
{
    int mid;
    int head = 0, tail = n ;
    while (head < tail)
    {
        mid = (tail + head) >> 1;
        if(num[mid] == 1) {
            tail = mid;
        }else{
            head = mid + 1;
        }
    }
    if(tail == n){
        return -1;
    }
    return tail;
}

int main()
{
    int arr1[10] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    int arr2[10] = {1, 1, 1, 1, 1, 1, 0, 0, 0, 0};
    int arr3[10] = {0, 0, 0, 0, 0, 0, 0, 1, 1, 1};

    P(binarySearch(arr1, 10, 13));
    P(binarySearch1(arr2, 10));
    P(binarySearch2(arr3, 10));
    return 0;
}
