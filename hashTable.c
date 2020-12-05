//
// Created by Xin Sun on 2020-12-04.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *str;
    struct Node *next;
}Node;

typedef struct HashTable{
    Node **data;
    int size;
}HashTable;

Node *init_node(char *str, Node *head)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->str = strdup(str);
    node->next = head;

    return node;
}

HashTable *init_hashTable(int n)
{
    HashTable *h= (HashTable *)malloc(sizeof(HashTable));
    h->size = n << 1;
    h->data = (Node **)calloc(h->size, sizeof(Node *));

    return h;
}

int BKDRHash(char *str)
{
    int seed = 31;
    int hash = 0;
    for(int i=0; str[i]; i++) hash = hash *seed + str[i];

    return hash & 0x7fffffff;
}

int insert(HashTable *h, char *str)
{
    if(h == NULL) return 0;
    int hash = BKDRHash(str);
    int index = hash % h->size;
    Node *node = init_node(str, h->data[index]);
    h->data[index] = node;

    return 1;
}

int search(HashTable *h, char *str)
{
    if(h == NULL) return 0;
    int hash = BKDRHash(str);
    int ind = hash % h->size;
    Node *node = h->data[ind];
    while(node && strcmp(str, node->str)){
        node = node->next;
    }

    return node != NULL;
}

void clear_node(Node *node)
{
    if(node == NULL) return;
    Node *p = node, *q;
    while(p)
    {
        q = p->next;
        free(p->str);
        free(p);
        p = q;
    }
}

void clear(HashTable *h)
{
    if(h == NULL) return;
    for(int i=0; i<h->size; i++){
        clear_node(h->data[i]);
    }
    free(h->data);
    free(h);

    return;
}
int main()
{
    int op;
#define max_n 100
    HashTable *h = init_hashTable(max_n);
    char *str[max_n + 5] = {0};
    while(~scanf("%s%d", str, &op)){
        switch(op){
            case 0:
                printf("insert to hash table%s\n", str);
                insert(h, str);
                break;
            case 1:
                printf("search %s from hash table=%d\n", str, search(h, str));
                break;
        }
    }
#undef max_n
    clear(h);
    return 0;
}