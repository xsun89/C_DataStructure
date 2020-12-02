//
// Created by Xin Sun on 2020-12-01.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
typedef struct Node {
    char data;
    struct Node *lchild;
    struct Node *rchild;
}Node;

typedef struct Tree {
    Node *root;
    int n;
}Tree;

typedef struct Stack {
    Node **stackData;
    int top, size;
}Stack;

Stack *init_stack(int size)
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->stackData = (Node **)malloc(sizeof(Node *) * size);
    stack->size = size;
    stack->top = -1;

    return stack;
}

void clear_stack(Stack *stack)
{
    if(stack == NULL) return;
    free(stack->stackData);
    free(stack);

    return;
}

int push_stack(Stack *stack, Node *node)
{
    if(stack == NULL) return 0;
    if(stack->top == stack->size) return 0;
    stack->stackData[++stack->top] = node;

    return 1;
}

int empty_stack(Stack *stack)
{
    if(stack == NULL) return 1;
    return stack->top == -1;
}
int pop_stack(Stack *stack)
{
    if(stack == NULL) return 0;
    if(stack->top == -1) return 0;
    stack->top--;
    return 1;
}

Node *top(Stack *stack)
{
    if(stack == NULL) return NULL;
    return stack->stackData[stack->top];
}
Node *getNewNode(char val){
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

void pre_order_node(Node *node)
{
    if(node == NULL) return;
    printf("%c ", node->data);
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
    printf("%c ", node->data);
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
    printf("%c ", node->data);

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
    printf("%c ", root->data);
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
/*
 *
 *A(B(,D),C(,E))
 *when meet character, create node, when meet (, insert to stack, when meet ), pop from stack in order to
 * get to root node for this node inside (), when meet ,means before , it is left node, after , it is right
 * node.
 */
Node *build(const char *str, int *node_num)
{
    Stack *stack = init_stack(strlen(str));
    int flag = 0;
    Node *tmp = NULL, *p = NULL;
    while(str[0])
    {
        switch(str[0])
        {
            case ' ':break;
            case '(':
                push_stack(stack, tmp);
                flag = 0;
                break;
            case ')':
                p = top(stack);
                pop_stack(stack);
                break;
            case ',':
                flag = 1;
                break;
            default:
                tmp = getNewNode(str[0]);
                if(!empty_stack(stack) && flag == 0)
                {
                    top(stack)->lchild = tmp;
                }else if(!empty_stack(stack) && flag == 1){
                    top(stack)->rchild = tmp;
                }
                (*node_num)++;
                break;
        }
        ++str;
    }
    if(tmp != NULL && p == NULL) p = tmp;

    return p;
}

int main()
{
    char str[1000];
    int node_num = 0;
    scanf("%[^\n]s", str);
    Tree *tree = getNewTree();
    tree->root = build(str, &node_num);
    tree->n = node_num;
    pre_order(tree);
    in_order(tree);
    post_order(tree);
    return 0;
}