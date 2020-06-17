BinTree Q[1000];
int i=-1;
void in_order(BinTree T);
int Height(BinTree T);
int CheckBST(BinTree T,int K){
    int h;
    int j;
    int height;
    in_order(T);
    height=Height(T);
    h=0;
    while(Q[h]!=0) h++;
    for(j=0;j<h-1;j++)
        if(Q[j]->Key>=Q[j+1]->Key) return -height;
        return Q[h-K]->Key;
}
void in_order(BinTree T){
    if(!T);
    else{
        in_order(T->Left);
        Q[++i]=T;
        in_order(T->Right);
    }
}
int Height(BinTree T){
    int front=-1,rear=-1,last=0,level=0;
    if(!T) return 0;
    BinTree p=T,D[1000];
    D[++rear]=p;
    while(front<rear){
        p=D[++front];
        if(p->Left)
        D[++rear]=p->Left;
        if(p->Right)
        D[++rear]=p->Right;
        if(front==last){
            level++;
            last=rear;
        } 
    }
    return level;
 }