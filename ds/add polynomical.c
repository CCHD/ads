Polynomial Add( Polynomial a, Polynomial b ){
	Polynomial sdummy,sum,an,bn;
	int coef;
	sdummy=(Polynomial)malloc(sizeof(struct Node));
    sum=sdummy->Next=NULL;
    an=a->Next;
	bn=b->Next;
	if(an==NULL) 
		for(;bn!=NULL;){
		if(bn->Coefficient==0) bn=bn->Next;
		else{
			sum=(Polynomial)malloc(sizeof(struct Node));
	sum->Coefficient=bn->Coefficient;
	sum->Exponent=bn->Exponent;
	sum->Next=NULL;
	bn=bn->Next;
	sum=sum->Next;
}
	}
	else if(bn==NULL)
		for(;an!=NULL;){
	if(an->Coefficient==0) an=an->Next;
		else{
			sum=(Polynomial)malloc(sizeof(struct Node));
    sum->Coefficient=an->Coefficient;
    sum->Exponent=an->Exponent;
    sum->Next=NULL;
    an=an->Next;
    sum=sum->Next;
	}
	}
	else{
	for(;(an!=NULL)&&(bn!=NULL);){
    if(an->Exponent==bn->Exponent){
     coef=an->Coefficient+bn->Coefficient;
     if(coef==0){
     an=an->Next;
     bn=bn->Next;
     }
    else{
    	sum=(Polynomial)malloc(sizeof(struct Node));
    sum->Coefficient=coef;
    sum->Exponent=an->Exponent;
    sum->Next=NULL;
    an=an->Next;
    bn=bn->Next;
    sum=sum->Next;
    }
	}
	else if(an->Exponent>bn->Exponent){
		if(an->Coefficient==0) an=an->Next;
		else{
			sum=(Polynomial)malloc(sizeof(struct Node));
    sum->Coefficient=an->Coefficient;
    sum->Exponent=an->Exponent;
    sum->Next=NULL;
    an=an->Next;
    sum=sum->Next;
	}
}
	else{
		if(bn->Coefficient==0) bn=bn->Next;
		else{
			sum=(Polynomial)malloc(sizeof(struct Node));
	sum->Coefficient=bn->Coefficient;
	sum->Exponent=bn->Exponent;
	sum->Next=NULL;
	bn=bn->Next;
	sum=sum->Next;
	}
}
	}
	if(an==NULL)
	for(;bn!=NULL;){
		if(bn->Coefficient==0) bn=bn->Next;
		else{
			sum=(Polynomial)malloc(sizeof(struct Node));
	sum->Coefficient=bn->Coefficient;
	sum->Exponent=bn->Exponent;
	sum->Next=NULL;
	bn=bn->Next;
	sum=sum->Next;
}
	}
	else 
	for(;an!=NULL;){
	if(an->Coefficient==0) an=an->Next;
		else{
			sum=(Polynomial)malloc(sizeof(struct Node));
    sum->Coefficient=an->Coefficient;
    sum->Exponent=an->Exponent;
    sum->Next=NULL;
    an=an->Next;
    sum=sum->Next;
	}
	} 
}
	return sdummy;
}

   
