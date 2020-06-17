Deque CreateDeque(){
	Deque D;
	D = (Deque)malloc(sizeof(struct DequeRecord));
	D->Front = D->Rear = (PtrToNode)malloc(sizeof(struct Node));
	D->Front->Next = D->Rear->Last = NULL;
	return D;
} 
int Push( ElementType X, Deque D ){
	PtrToNode tmp;
	tmp = (PtrToNode)malloc(sizeof(struct Node));
	if(!tmp)
		return 0;
	tmp->Element = X;
	tmp->Last = D->Front;
	tmp->Next = D->Front->Next;
	if(D->Front->Next){
		D->Front->Next->Last = tmp;
		D->Front->Next = tmp;
	}
	else
		D->Front->Next = D->Rear = tmp;
	return 1;
}
ElementType Pop( Deque D ){
	PtrToNode tmp;
	if(D->Front == D->Rear)
		return ERROR;
	tmp = D->Front->Next;
	D->Front->Next = D->Front->Next->Next;	
	if(tmp != D->Rear)
		D->Front->Next->Last = D->Front;
	else
		D->Rear = D->Front;
	return tmp->Element;
}
int Inject( ElementType X, Deque D ){
	PtrToNode tmp;
	tmp = (PtrToNode)malloc(sizeof(struct Node));
	if(!tmp)
		return 0;
	tmp->Element = X;
	tmp->Next = NULL;
	tmp->Last = D->Rear;
	D->Rear = tmp;
	D->Rear->Last->Next = tmp;
	return 1;	
}
ElementType Eject( Deque D ){
	PtrToNode tmp;
	if(D->Rear == D->Front)
		return ERROR;
	tmp = D->Rear;	
	D->Rear = D->Rear->Last;
	D->Rear->Next = NULL;
	return tmp->Element;
}