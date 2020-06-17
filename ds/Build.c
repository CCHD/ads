#include<stdio.h>
#include<stdlib.h>
#define Nochild -1
typedef struct node *BinTree;
struct node{
	int l;
	int r;
	int Key;
	struct node *Left;
	struct node *Right;
};
BinTree PreCreate();
void InCreate(BinTree T);
void Sort(int N);
void Level(BinTree T);
int count;
int N;
int a[100];
BinTree A[100];
int main(){
    int i;
	BinTree T;
	scanf("%d",&N);
	if(N==0) return 0;
	count=N;
	T=PreCreate();
	 for(i=0;i<N;i++)
    scanf("%d",&a[i]);
    Sort(N);
	InCreate(T);
    Level(T);
    for(i=0;i<N;i++){
    	if(i==0) printf("%d",A[i]->Key);
    else printf(" %d",A[i]->Key);
}
    return 0;
}
void Sort(int N){
	int i,j;
	for(i=0;i<N-1;i++)
	   for(j=0;j<N-1-i;j++){
	   if(a[j]>a[j+1]){
	      int temp=a[j];
	      a[j]=a[j+1];
	      a[j+1]=temp;
	   }
	   }
}
BinTree PreCreate(){
	BinTree BST=malloc(sizeof(BinTree)*N);
    if(count){
	scanf("%d%d",&BST->l,&BST->r);
	count--;
	if(BST->l==Nochild) BST->Left=NULL;
	else BST->Left=PreCreate();
	if(BST->r==Nochild) BST->Right=NULL;
	else BST->Right=PreCreate();
}
    return BST;
}
int i;
void InCreate(BinTree T){
     if(!T) ;
     else{
     InCreate(T->Left);
     T->Key=a[i++];
     InCreate(T->Right);
     }
}
void Level(BinTree T){
    BinTree p=T;
	int front=-1,rear=-1;
	A[++rear]=T;
	while(front<rear){
    p=A[++front];
    if(p->Left) 
    A[++rear]=p->Left;
    if(p->Right)
    A[++rear]=p->Right;
	}
}