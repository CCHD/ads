#include<stdio.h>
#include<stdlib.h>
#define Max 10
int G[Max][Max];
int visit[Max];
int stack[Max],queue[Max+1];
int front;
int rear;
int N,E;
int top=-1;
void init();
void dfs(int v);
void bfs(int v);
void Print();
int main(){
	init();
	int i;
    memset(visit,0,N*sizeof(visit[0]));
    for(i=0;i<N;i++){
        if(!visit[i]){
           dfs(i);
           Print();
        }
    }
    memset(visit,0,N*sizeof(visit[0]));
    for(i=0;i<N;i++){
       if(!visit[i])
          bfs(i);
          front=rear=0;
    }
}
void init(){
	int i,v,w;
	scanf("%d%d",&N,&E);
	for(i=0;i<E;i++){
	scanf("%d%d",&v,&w);
	G[v][w]=G[w][v]=1;
	}
}
void dfs(int v){
	visit[v]=1;
	stack[++top]=v;
	int i;
	for(i=0;i<N;i++){
        if(G[v][i]==1&&!visit[i])
           dfs(i);
	}
}
void bfs(int v){
	visit[v]=1;
    int i;
    queue[rear++]=v;
    for(;front!=rear;front++){
        v=queue[front];
        for(i=0;i<N;i++){ 
            if(G[v][i]==1&&!visit[i]){
              queue[rear++]=i;
              visit[i]=1;
            }
        }
    }
    front=0;
    printf("{ ");
    while(front!=rear){
         printf("%d ",queue[front++]);
    }
    printf("}\n");
}
void Print(){
	int i=-1;
    printf("{ ");
	while(i!=top){
	     printf("%d ",stack[++i]);
	}
	printf("}\n");
	top=-1;
}