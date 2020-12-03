//
// Created by Xin Sun on 2020-12-02.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_N

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

void output(int *data, int n)
{
    for (int i = 0; i <10; i++) {
        printf("%d\n", data[i]);
    }
    printf("\n");
}
int main()
{
    srand(time(0));

    int num[20];
    int n = 20;
    for (int i = 0; i <n; i++){
        num[i] = rand()%100;
    }
    output(num, 20);

    //insert_sort(num, 10);
    bubble_sort(num, 20);
    output(num, 20);
    return 0;
}