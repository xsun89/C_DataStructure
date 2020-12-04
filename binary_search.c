//
// Created by Xin Sun on 2020-12-04.
//

#include <stdio.h>
#include <stdlib.h>

int binarySearch(int *num, int n, int x)
{
    int mid = n >> 1;
    int head = 0, tail = n-1;
    while(head <= tail){
        if(num[mid] == x){
            return mid;
        }else if(num[mid] > x){
            tail = mid -1;
        }else{
            head = mid + 1;
        }
    }

    return -1;
}

int main()
{
    int num[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int k = binarySearch(num, 10, 3);
    printf("%d\n", k);
    return 0;
}