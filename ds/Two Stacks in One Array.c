#define Empty -1
Stack CreateStack( int MaxElements ){
    Stack S;
	S=(Stack)malloc(sizeof(struct StackRecord));
    S->Capacity=MaxElements;
    S->Top1=-1;
    S->Top2=MaxElements;
    S->Array=(ElementType*)malloc(sizeof(ElementType)*MaxElements);
    return S;
}
int IsEmpty( Stack S, int Stacknum ){
	if(Stacknum==1) return S->Top1==Empty;
	else if(Stacknum==2) return S->Top2==S->Capacity;
	return 0;
}
int IsFull(Stack S){
	if(S->Top1+1==S->Top2) return 1;
	return 0;
}
int Push( ElementType X, Stack S, int Stacknum ){
	if(IsFull(S))  return 0;
	if(Stacknum==1){
	S->Array[++S->Top1]=X;
	}
	else if(Stacknum==2){
	S->Array[--S->Top2]=X;
	}
	return 1;
}
ElementType Top_Pop( Stack S, int Stacknum ){
     if(IsEmpty(S,Stacknum)) return ERROR;
     if(Stacknum==1) return S->Array[S->Top1--];
     else return S->Array[S->Top2++];
}


