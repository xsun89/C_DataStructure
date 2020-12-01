//
// Created by Xin Sun on 2020-11-25.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Queue {
    int *data;
    int head, tail, length, count;
} Queue;

Queue *init(int n)
{
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->data = (int *)malloc(n * sizeof(int));
    q->length = n;
    q->head = 0;
    q->tail = 0;
    q->count = 0;

    return q;
}

void clear(Queue *q)
{
    if(q == NULL) return;
    free(q->data);
    free(q);

    return;
}

int front(Queue *q)
{
    return q->data[q->head];
}
int empty(Queue *q)
{
    if(q == NULL) return 0;
    return q->count == 0;
}
int pop(Queue *q)
{
    if(q == NULL) return 0;
    if(q->count == 0) return 0;
    q->head++;
    if(q->head == q->length) q->head = 0;

    q->count--;
    return 1;
}

int expend(Queue *q)
{
    if(q == NULL) return 0;
    int expend_size = q->length;
    int *p;
    while(expend_size){
        p = (int *)malloc(sizeof(int)*(q->length + expend_size));
        if(p){
            break;
        }
        expend_size >>= 1;
    }
    if(p == NULL) return 0;
    for(int i=q->head, j=0; j<q->count; j++){
        p[j] = q->data[(i + j) % q->length];
    }
    free(q->data);
    q->data = p;
    q->length += expend_size;
    q->head = 0;
    q->tail = q->count;
    return 1;

}

int push(Queue *q, int val)
{
    if(q == NULL) return 0;
    if(q->count == q->length){
        printf("Need to Expend!\n");
        if(expend(q) == 0){
            return 0;
        }
    }
    q->data[q->tail] = val;
    q->tail++;
    if(q->tail == q->length) q->tail = 0;

    q->count++;
    return 1;
}

void output(Queue *q)
{
    if(q == NULL) return;
    printf("Queue = [");
    for(int i = q->head, j=0; j < q->count; j++){
        j && printf(", ");
        printf("%d", q->data[(i + j)% q->length]);
    }
    printf("]\n");

    return;
}

int main()
{
    srand(time(0));
#define MAX_OP 20
    Queue *q = init(2);
    for(int i=0; i<MAX_OP; i++){
        int val = rand() % 100;
        int op = rand() % 4;
        switch(op){
            case 0:
            case 1:
            case 2:
                printf("push %d to Queue ! ", val);
                printf("result = %d\n", push(q, val));
                break;
            case 3:
                printf("pop %d from queue! ", front(q));
                printf("result = %d\n", pop(q));
                break;
        }
        output(q);
        printf("\n");
    }

    clear(q);
    return 0;
}