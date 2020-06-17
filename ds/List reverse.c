#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
struct Node {
    ElementType Element;
    Position Next;
};

List Read(); /* details omitted */
void Print( List L ); /* details omitted */
List Reverse( List L );

int main()
{
    List L1, L2;
    L1 = Read();
    L2 = Reverse(L1);
    Print(L1);
    Print(L2);
    return 0;
}
List Read(){
	int i,n;
    int element;
    List dummy,pNode,pTail;
    dummy=(List)malloc(sizeof(struct Node));
    pNode=pTail=NULL;
    dummy->Next=NULL;
    scanf("%d",&n);
    if(n==0) dummy->Next=NULL;
    for(i=1;i<=n;i++){
    pNode=(List)malloc(sizeof(struct Node));
    scanf("%d",&element);
    pNode->Element=element;
    pNode->Next=NULL;
    if(dummy->Next==NULL)
        dummy->Next=pNode;
    else pTail->Next=pNode;
    pTail=pNode;
    }
    return dummy;
}
void Print( List L ){
	L=L->Next;
    if(L==NULL) printf("error");
    else
	while(L!=NULL){
	printf("%d ",L->Element);
	L=L->Next;
	}
}
List Reverse(List L){
    int r[1000];
	List dummy,pNode,pTail;
    dummy=(List)malloc(sizeof(struct Node));
    dummy->Next=NULL;
    if(L->Next==NULL) dummy->Next=NULL;
    pTail=L->Next;
    int i;
    for(i=1;pTail!=NULL;i++){
    r[i]=pTail->Element;
    pTail=pTail->Next;
    }
    for(i=i-1;i>=1;i--){
    pNode=(List)malloc(sizeof(struct Node));
    pNode->Element=r[i];
    pNode->Next=NULL;
    L->Next->Element=r[i];
    L=L->Next;
    if(dummy->Next==NULL) dummy->Next=pNode;
    else pTail->Next=pNode;
    pTail=pNode;

    }
    return dummy;
}