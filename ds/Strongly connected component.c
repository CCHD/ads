int dfn[MaxVertices],low[MaxVertices],top,time,is_in_stack[MaxVertices];
int stack[MaxVertices];
int min(int a,int b){
	if(a>b)
	return b;
	else return a;
}
void tarjan(Graph G,int v){
	PtrToVNode node=G->Array[v];
	int child,tmp;
	stack[++top]=v;
	is_in_stack[v]=1;
	dfn[v]=low[v]=++time;
	while(node!=NULL){
	    child=node->Vert;
	    //未曾访问过的点
	    if(dfn[child]==-1){
	       tarjan(G,child);
	       low[v]=min(low[child],low[v]);
	    }
	    //如果点在栈，那么low[v]=min(low[v],dfn[u])
	    else if(is_in_stack[child]==1){
	     low[v]=min(low[v],dfn[child]);
	    }
	    node=node->Next;
	}
	//出栈
	if(dfn[v]==low[v]){
	   do{
	      tmp=stack[top--];
	      printf("%d ",tmp);
	      is_in_stack[tmp]=0;
	   }while(tmp!=v);
	   printf("\n");
	}

}
void StronglyConnectedComponents( Graph G, void (*visit)(Vertex V) ){
	int i;
	for(i=0;i<G->NumOfVertices;i++){
	   dfn[i]=-1;
       low[i]=is_in_stack[i]=0;
	}
	top=-1;
	time=0;
	//避免由于存在独立点的情况
	for(i=0;i<G->NumOfVertices;i++){
	    if(dfn[i]==-1)
	    tarjan(G,i);
}
}