void PercolateUp( int p, PriorityQueue H ){
	int i;
	ElementType temp;
	temp=H->Elements[p];
	for(i=p;H->Elements[i/2]>temp;i/=2){
	   H->Elements[i]=H->Elements[i/2];
	}
	H->Elements[i]=temp;
}
void PercolateDown( int p, PriorityQueue H ){
	int child;
	ElementType temp;
	temp=H->Elements[p];
    for(p=1;p*2<=H->Size;p=child){
    child=p*2;
    if(child!=H->Size&&H->Elements[child+1]<H->Elements[child])
    child++;
    if(temp>H->Elements[child])
    H->Elements[p]=H->Elements[child];
    else break;
    }
    H->Elements[p]=temp;
}