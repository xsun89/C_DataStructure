//
// Created by Xin Sun on 2020-11-27.
//

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct Stack{
    char *data;
    int maxsize;
    int top;
}Stack;

Stack *initStack(int maxsize)
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->maxsize = maxsize;
    stack->top = -1;
    stack->data = (char *)malloc(sizeof(char) * maxsize);

    return stack;
}

void clear(Stack *s)
{
    if(s == NULL){
        return;
    }
    free(s->data);
    free(s);

    return;
}

int pop(Stack *stack)
{
    if(stack == NULL) return 0;
    if(stack->top == -1) return 0;
    stack->top--;

    return 1;
}
int expend(Stack *stack)
{
    if(stack == NULL) return 0;
    int expend_size = stack->maxsize;
    char *p = NULL;
    while(expend_size)
    {
         p = (char *)realloc(stack->data, stack->maxsize+expend_size);
        if(p){
            break;
        }
        expend_size >>= 1;
    }
    if(p == NULL) return 0;
    stack->data = p;
    stack->maxsize += expend_size;
    return 1;
}
int push(Stack *stack, char val)
{
    if(stack == NULL) return 0;
    if(stack->top == stack->maxsize-1){
        if(!expend(stack)){
            return 0;
        }
        printf("expend successfully!");
    }
    stack->data[++stack->top] = val;

    return 1;
}

bool empty(Stack *stack){
    return stack->top == -1;
}

char seek(Stack *stack)
{
    if(stack == NULL) return NULL;
    if(stack->top == -1) return NULL;
    return stack->data[stack->top];
}

char top(Stack *stack)
{

    if(stack == NULL) return NULL;
    if(empty(stack)) return NULL;
    return stack->data[stack->top];
}

void output(Stack *stack)
{
    if(stack == NULL) return;
    printf("[");
    for(int i=0; i<=stack->top; i++)
    {
        i && printf(", ");
        printf("%d", stack->data[i]);
    }
    printf("]\n");

    return;
}
bool isValid(Stack *stack, char *str)
{
    int isValid = 0;
    int size = strlen(str);
    for(int i = 0; i < size; i++) {
        switch (str[i]) {
            case '(':
            case '[':
            case '{':
                push(stack, str[i]);
                break;
            case ')':
                if(empty(stack)) return false;
                if(seek(stack) != '(') return false;
                pop(stack);
                break;
            case ']':
                if(empty(stack)) return false;
                if(seek(stack) != '[') return false;
                pop(stack);
                break;
            case '}':
                if(empty(stack)) return false;
                if(seek(stack) != '{') return false;
                pop(stack);
                break;

        }
    }

    return empty(stack);
}
int main()
{
    char *str = "{[()]}";
    Stack *stack = initStack(strlen(str));

    printf("%d\n", isValid(stack, str));

    return 0;

}