#include <stdio.h>
#include <stdlib.h>

typedef struct node BST;
struct node{
    int key;
    struct node *l_child, *r_child;
};

BST *T;
int *inorder, *val;
int j = 0;

int Comp(const void *a, const void *b){
    return *(int*)a - *(int*)b;
}

void Inorder(BST *root){
    if(NULL == root){
        return;
    }
    
    Inorder(root->l_child);
    root->key = val[j];
    j++;
    Inorder(root->r_child);
}

int main(void) {
    int size, i, l_child, r_child, tail = 1;
    BST *Q;
    int *visit;
    
    scanf("%d", &size);
    T = (BST*)malloc(sizeof(BST) * size);
    Q = (BST*)malloc(sizeof(BST) * size);
    val = (int*)malloc(sizeof(int) * size);
    inorder = (int*)malloc(sizeof(int) * size);
    visit = (int*)calloc(size, sizeof(int));
    for(i = 0; i < size; i++){
        scanf("%d%d", &l_child, &r_child);
        if(-1 != l_child){
            T[i].l_child = T + l_child;
            visit[l_child] = 1;
        }
        else{
            T[i].l_child = NULL;
        }
        if(-1 != r_child){
            T[i].r_child = T + r_child;
            visit[r_child] = 1;
        }
        else{
            T[i].r_child = NULL;
        }
    }
    for(i = 0; i < size; i++){
        scanf("%d", val + i);
    }
    qsort(val, size, sizeof(int), Comp);

    Inorder(T);
    Q[0] = T[0];
    for(i = 0; i < size; i++){
        if(0 == i){
            printf("%d", Q[i].key);
        }
        else{
            printf(" %d", Q[i].key);
        }
        
        if(NULL != Q[i].l_child){
            Q[tail++] = *(Q[i].l_child);
        }
        if(NULL != Q[i].r_child){
            Q[tail++] = *(Q[i].r_child);
        }
    }
    
    return 0;
}
