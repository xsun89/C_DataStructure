//
// Created by Xin Sun on 2020-12-05.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define swap(a,b){\
    __typeof(a) __tmp = a;\
    a = b; \
    b = __tmp;\
}
typedef struct PriorityQueue {
    int *data;
    int cnt, size;
}PriorityQueue;

PriorityQueue *init(int n)
{
    PriorityQueue *p = (PriorityQueue *)malloc(sizeof(PriorityQueue));
    p->data = (int *)malloc(sizeof(int)*(n+1));
    p->cnt = 0;
    p->size = n;
    return p;
}

int empty(PriorityQueue *p)
{
    return p->cnt == 0;
}

int top(PriorityQueue *p)
{
    return p->data[1];
}

int push(PriorityQueue *p, int val)
{
    if(p == NULL) return 0;
    if(p->cnt == p->size) return 0;

    p->data[++(p->cnt)] = val;
    int ind = p->cnt;
    while(ind >> 1 && p->data[ind] > p->data[ind >>1]){
        swap(p->data[ind], p->data[ind >>1]);
        ind >>= 1;
    }
    return 1;
}

int pop(PriorityQueue *p)
{
    if(p == NULL) return 0;
    if(empty(p)) return 0;
    p->data[1] = p->data[p->cnt--];
    int ind = 1;
    while((ind << 1) <= p->cnt){
        int tmp = ind, l = ind << 1, r =ind<<1|1;
        if(p->data[l] > p->data[tmp]) tmp = l;
        if(r <= p->cnt && p->data[r] > p->data[tmp]) tmp = r;
        if(tmp == ind){
            break;
        }
        swap(p->data[tmp], p->data[ind]);
        ind = tmp;
    }
    return 1;
}

void clear(PriorityQueue *p)
{
    if(p == NULL) return;
    free(p->data);
    free(p);
    return;
}

void output(PriorityQueue *p)
{
    if(p == NULL) return;
    printf("cnt =%d\n", p->cnt);
    printf("Queue = [");
    for(int i = 1; i <= p->cnt; i++){
        (i-1) && printf(", ");
        printf("%d", p->data[i]);
    }
    printf("]\n");

    return;
}

int main()
{
    srand(time(0));
#define MAX_OP 20
    PriorityQueue *q = init(MAX_OP);
    printf("%d\n", q->size);
    for(int i=0; i<MAX_OP; i++){
        int val = rand() % 100;
        printf("push %d to Queue ! ", val);
        printf("result = %d\n", push(q, val));
        printf("\n");
    }
    for(int i=0; i<MAX_OP; i++){
        printf("%d ", top(q));
        pop(q);
    }
#undef MAX_OP
    printf("\n");
    clear(q);
    return 0;
}