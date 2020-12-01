//
// Created by Xin Sun on 2020-11-29.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
typedef struct Node {
    int data;
    struct Node *lchild;
    struct Node *rchild;
}Node;

typedef struct Tree {
    Node *root;
    int n;
}Tree;

Node *getNewNode(int val){
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = val;
    node->lchild = NULL;
    node->rchild = NULL;

    return node;
}

Tree *getNewTree()
{
    Tree *tree = (Tree *)malloc(sizeof(Tree));
    tree->root = NULL;
    tree->n = 0;

    return tree;
}

void clearNode(Node *node)
{
    if(node == NULL) return;
    clearNode(node->lchild);
    clearNode(node->rchild);
    free(node);

    return;
}

void clear(Tree *tree)
{
    if(tree == NULL) return;
    clearNode(tree->root);
    free(tree);

    return;
}

Node *insert_node(Node *root, int val, int *flag)
{
    if(root == NULL){
        *flag = 1;
        return getNewNode(val);;
    }
    if(root->data == val) return root;
    if(root->data > val) {
        root->lchild = insert_node(root->lchild, val, flag);
    }else {
        root->rchild = insert_node(root->rchild, val, flag);
    }

    return root;
}

void insert(Tree *tree, int val)
{
    int flag = 0;
    tree->root = insert_node(tree->root, val, &flag);
    tree->n += flag;
    return;
}

void pre_order_node(Node *node)
{
    if(node == NULL) return;
    printf("%d ", node->data);
    pre_order_node(node->lchild);
    pre_order_node(node->rchild);

    return;
}
void pre_order(Tree *tree)
{
    if(tree == NULL) return;
    printf("pre_order: ");
    pre_order_node(tree->root);
    printf("\n");

    return;
}

void in_order_node(Node *node)
{
    if(node == NULL) return;

    in_order_node(node->lchild);
    printf("%d ", node->data);
    in_order_node(node->rchild);

    return;
}
void in_order(Tree *tree)
{
    if(tree == NULL) return;
    printf("in_order: ");
    in_order_node(tree->root);
    printf("\n");

    return;
}

void post_order_node(Node *node)
{
    if(node == NULL) return;

    post_order_node(node->lchild);
    post_order_node(node->rchild);
    printf("%d ", node->data);

    return;
}
void post_order(Tree *tree)
{
    if(tree == NULL) return;
    printf("post_order: ");
    post_order_node(tree->root);
    printf("\n");

    return;
}

void output_node(Node *root)
{
    if(root == NULL) return;
    printf("%d ", root->data);
    if(root->lchild == NULL && root->rchild == NULL) return;
    printf("(");
    output_node(root->lchild);
    printf(",");
    output_node(root->rchild);
    printf(")");
    return;
}
void output(Tree *tree){
    if(tree == NULL) return;
    printf("Tree: ");
    output_node(tree->root);
    printf("\n");

    return;
}
int main()
{
    srand(time(0));
#define MAX_OP 20
    Tree *t = getNewTree();
    for(int i=0; i<MAX_OP; i++){
        int val = rand() % 100;
        printf("insert %d to Tree ! ", val);
        insert(t, val);
        output(t);
    }
    pre_order(t);
    in_order(t);
    post_order(t);
    clear(t);
    return 0;
}
