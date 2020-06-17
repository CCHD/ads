typedef struct StackRecord *Stack;
struct StackRecord{
	    int Top;
        ElementType Array[Max_Expr];
	};
int IsEmpty(Stack S);
int IsFull(Stack S);
void Push(ElementType X,Stack S);
ElementType Top(Stack S);
void Pop(Stack S);
ElementType EvalPostfix(char *expr){
	Stack S;
	S=(Stack*)malloc(sizeof(struct StackRecord));
	char Trans[Max_Expr];
	S->Top=0;
	S->Array[0]=0;
    int i=0,m=0;
    ElementType v;
    ElementType top1,top2;
    while(expr[i]!='\0'){
    m++;
    i++;
    }
    i=0;
    while(expr[i]!=' '&&expr[i]!='\0'){
         if(expr[i]=='+'||(expr[i]=='-'&&(!(expr[i+1]>='0'&&expr[i+1]<='9')))||expr[i]=='*'||expr[i]=='/'){
                  if(S->Top<=0) return v=Infinity;
                  top1=Top(S);
                  if(expr[i]=='/'&&top1==0) return v=Infinity;
                  else {
                  Pop(S);
                  if(IsEmpty(S)) return v=Infinity;
                  else
                  {
                  top2=Top(S);
                  Pop(S);
         }
    }
    switch(expr[i]){
    case '+':v=top1+top2;break;
    case '-':v=top2-top1;break;
    case '*':v=top1*top2;break;
    case '/':v=top2/top1;break;
    }
    Push(v,S);
    if(expr[i+1]=='\0'&&S->Top>0) return v=Infinity;
    else if(expr[i+1]=='+'||expr[i+1]=='/'||expr[i+1]=='-'||expr[i+1]=='*') i+=2;
    else i++;
    }
        else{
        int j=0;
        double element=0;
        if(expr[i]=='-'){
        i++;
        while(expr[i]!=' '){
              Trans[j++]=expr[i];
              i++;
              }
        i++;
        Trans[j]='\0';
        element=atof(Trans);
        element=-element;
        Push(element,S);
        }
        else{
        while(expr[i]!=' '){
              Trans[j++]=expr[i];
              i++;
              }
        i++;
        Trans[j]='\0';
        element=atof(Trans);
        Push(element,S);
        }
        }
    if(IsFull(S)) return v=Infinity;
}
        if(S->Top==0) return v;
        if(S->Top>0) return v=Infinity;
}
void Push(ElementType X,Stack S){
    S=(Stack*)malloc(sizeof(struct StackRecord));
	S->Array[++S->Top]=X;
}
ElementType Top(Stack S){
	return S->Array[S->Top];
}
void Pop(Stack S){
	S->Top--;
}
int IsEmpty(Stack S){
	if(S->Top<0) return 1;
	return 0;
}
int IsFull(Stack S){
	if(S->Top>Max_Expr) return 1;
	return 0;
}



