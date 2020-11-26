//
// Created by Xin Sun on 2020-11-23.
//
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define COLOR(a, b) "\033[" #b "m" a "\033[0m"
#define GREEN(a) COLOR(a, 32)

typedef struct Vector{
    int *data;
    int length;
    int size;
} Vect;

Vect *init(int n)
{
    Vect *vec = (Vect *)malloc(sizeof(Vect));
    vec->data = (int *)malloc(n * sizeof(int));
    vec->length = 0;
    vec->size = n;
    return vec;
}

int expend(Vect *vec){
    int expend_size = vec->size;
    int *p;
    while(expend_size){
        p = realloc(vec->data, sizeof(int) * (vec->size + expend_size));
        if(p){
            break;
        }
        expend_size >>= 1;
    }
    if(expend_size == 0){
        return 0;
    }
    vec->data = p;
    vec->size += expend_size;

    return 1;
}

int insert(Vect *vec, int val, int index)
{
    if(vec==NULL) return 0;

    if(index > vec->length || index < 0) return 0;
    if(vec->length == vec->size){
        if(!expend(vec)){
            return 0;
        }
        printf(GREEN("Successfully expended to size=%d\n"), vec->size);
    }
    for(int i=vec->length; i>index; i--){
        vec->data[i] = vec->data[i-1];
    }

    vec->data[index] = val;
    vec->length += 1;
    return 1;
}

int erase(Vect *vec, int index)
{
    if(vec==NULL) return 0;
    if(vec->length == 0) return 0;
    if(index >= vec->length || index < 0) return 0;
    for(int i=index; i < vec->length-1; i++){
        vec->data[i] = vec->data[i+1];
    }

    vec->length -= 1;

    return 1;
}
void clear(Vect *vec){
    if(vec == NULL) return;
    free(vec->data);
    free(vec);
    return;
}

void output(Vect *vec)
{
    if(vec == NULL){
        return;
    }
    printf("Vector [");
    for(int i=0; i<vec->length; i++){
        i && printf(", ");
        printf("%d", vec->data[i]);
    }
    printf("]\n");
}

int main()
{
    srand(time(0));
#define MAX_OP 20
    Vect *vec = init(2);
    for(int i=0; i<MAX_OP; i++){
        int val = rand() % 100;
        int index = rand() % (vec->length +3) -1;
        int op = rand() % 4;
        switch(op){
            case 0:
            case 1:
            case 2:
                printf("Insert %d at %d into Vect %d\n", val, index, insert(vec, val, index));
                break;
            case 3:
                printf("Erase at %d for Vect %d\n", index, erase(vec, index));
                break;
        }
        output(vec);
        printf("\n");
    }

    clear(vec);

    return 0;

}