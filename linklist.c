//
// Created by Xin Sun on 2020-11-24.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct ListNode{
    int data;
    struct ListNode *next;
}ListNode;

typedef struct Linklist{
    ListNode head;
    int length;
}List;

ListNode *getNewNode(int);
List *getlist();
int insert(List *, int, int);
int erase (List *, int);
void clearNode(ListNode *);
void clear(List *);
void output(List *);
void reverse(List *);

int main()
{
    srand(time(0));
#define MAX_OP 20
    List *l = getlist();
    for(int i=0; i<MAX_OP; i++){
        int val = rand() % 100;
        int index = rand() % (l->length +3) -1;
        int op = rand() % 4;
        switch(op){
            case 0:
            case 1:
            case 2:
                printf("Insert %d at %d into Vect %d\n", val, index, insert(l, index, val));
                break;
            case 3:
                printf("Erase at %d for Vect %d\n", index, erase(l, index));
                break;
        }
        output(l);
        printf("\n");
    }

    clear(l);
    return 0;
}

ListNode *getNewNode(int val)
{
    ListNode *n = (ListNode *) malloc(sizeof(ListNode));
    n->data = val;
    n->next = NULL;
    return n;
}

List *getlist()
{
    List *l = (List *) malloc(sizeof(List));
    l->head.next = NULL;
    l->length = 0;
    return l;
}

void clearNode(ListNode *node)
{
    if(node == NULL) return;
    free(node);

    return;
}

void clear(List *l)
{
    if(l == NULL) return;
    ListNode *p = l->head.next, *q;

    while(p != NULL){
        q = p->next;
        clearNode(p);
        p = q;
    }
    free(l);

    return;
}

int insert(List *l, int ind, int val)
{
    if(l == NULL) return 0;
    if(ind < 0 || ind > l->length){
        return 0;
    }
    ListNode *p = &(l->head);
    while(ind --){
        p = p->next;
    }
    ListNode *q = getNewNode(val);
    q->next = p->next;
    p->next = q;

    l->length += 1;

    return 1;
}

int erase(List *l, int ind)
{
    if(l == NULL) return 0;
    if(ind < 0 || ind >= l->length){
        return 0;
    }

    ListNode *p = &(l->head), *q;
    while(ind--){
        p = p->next;
    }

    q = p->next;
    p->next = q->next;
    clearNode(q);
    l->length -= 1;

    return 1;

}

void reverse(List *l)
{
    if(l == NULL){
        return;
    }

    ListNode *p = l->head.next, *q;
    l->head.next = NULL;

    while(p){
        q = p->next;
        p->next = l->head.next;
        l->head.next = p;
        p = q;

    }
    return;
}
void output(List *l)
{
    if(l == NULL) return;
    printf("List(%d) = [", l->length);
    for(ListNode *p=l->head.next; p; p=p->next)
    {
        printf("%d->", p->data);
    }
    printf("NULL]\n");

    return;
}