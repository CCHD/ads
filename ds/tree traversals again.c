#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int count;
int flag;
typedef struct t_node *Tree;
struct t_node{
	int element;
    struct t_node *Left;
    struct t_node *Right;
};
Tree Create();
void post_order(Tree T);
int main(){
	Tree T;
	scanf("%d",&count);
	getchar();
	T=Create();
	post_order(T);
	return 0;
}
Tree Create(){
    char a[5];
    Tree t;
    if(count==0) return NULL;
    scanf("%s",a);
    if(strlen(a)==3)
       return NULL;
    count--;
    t=(Tree)malloc(sizeof(struct t_node));
    scanf("%d",&(t->element));
    t->Left = t->Right = NULL;
    getchar();
    t->Left=Create();
    t->Right=Create();
    return t;
}
void post_order(Tree T){
    if(T==NULL);
    else{
    post_order(T->Left);
    post_order(T->Right);
    if(flag==0){
      printf("%d",T->element);
      flag=1;
    }
    else if(flag==1) printf(" %d",T->element);
}
}