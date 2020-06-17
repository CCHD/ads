#include<stdio.h>
#include<stdlib.h>

typedef struct node *Tree;
typedef struct node *Node;

struct node{
	int value;
	Node left;
	Node right;
	int height;
};

int Height(Node T);
int Max(int a,int b);
Tree Insert(Tree T,int x);
Node SingleLeftRotation(Node T);
Node SingleRightRotation(Node T);
Node DoubleLeftRotation(Node T);
Node DoubleRightRotation(Node T);

int main(){
	int i,N;
	int in_value;
	Tree T;
	T=(Tree)malloc(sizeof(struct node));
    T=NULL;
    scanf("%d",&N);
    for(i=0;i<N;i++){
    scanf("%d",&in_value);
    T=Insert(T,in_value);
    }
    printf("%d",T->value);
}

int Height(Node T){
	if(T==NULL)
	return -1;
	else return T->height;
}

int Max(int a,int b){
    int maximum;
	return maximum=a>b?a:b;
}

Tree Insert(Tree T,int x){
	if(T==NULL){
	  T=(Tree)malloc(sizeof(struct node));
	  if(T==NULL)
	     FatalError("Out of space!");
	  else{
	     T->value=x;
	     T->left=NULL;
	     T->right=NULL;
	     T->height=0;
	  }
	}
	else{
	   if(x<T->value){
	     T->left=Insert(T->left,x);
	     if(Height(T->left)-Height(T->right)==2){
	        if(x<T->left->value)
	          T=SingleLeftRotation(T);
	        else 
	          T=DoubleLeftRotation(T);
	     }
	   }
	   else if(x>T->value){
	     T->right=Insert(T->right,x);
	     if(Height(T->left)-Height(T->right)==-2){
	       if(x>T->right->value)
	         T=SingleRightRotation(T);
	       else
	         T=DoubleRightRotation(T);
	     }
	   }
	}
	T->height=Max(Height(T->left),Height(T->right))+1;
    return T;
}

Node SingleLeftRotation(Node T){
	Node Tn;
	Tn=T->left;
	T->left=Tn->right;
	Tn->right=T;
	T->height=Max(Height(T->left),Height(T->right))+1;
	Tn->height=Max(Height(T->left),Height(T->right))+1;
	return Tn;
}

Node SingleRightRotation(Node T){
	Node Tn;
	Tn=T->right;
	T->right=Tn->left;
	Tn->left=T;
	T->height=Max(Height(T->left),Height(T->right))+1;
	Tn->height=Max(Height(T->left),Height(T->right))+1;
	return Tn;
}

Node DoubleLeftRotation(Node T){
	T->left=SingleRightRotation(T->left);
	return SingleLeftRotation(T);
}

Node DoubleRightRotation(Node T){
	T->left=SingleLeftRotation(T->right);
	return SingleRightRotation(T);

}