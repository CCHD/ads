#include <stdio.h>  
#include <stdlib.h>  
  
typedef enum {false, true} bool;  
#define INFINITY 1000000  
#define MaxVertexNum 10  /* maximum number of vertices */  
typedef int Vertex;      /* vertices are numbered from 0 to MaxVertexNum-1 */  
typedef int WeightType;  
  
typedef struct GNode *PtrToGNode;  
struct GNode{  
    int Nv;  
    int Ne;  
    WeightType G[MaxVertexNum][MaxVertexNum];  
};  
typedef PtrToGNode MGraph;  
  
MGraph ReadG(); /* details omitted */  
  
void ShortestDist( MGraph Graph, int dist[], int path[], Vertex S );  
  
int main()  
{ 
    int dist[MaxVertexNum], path[MaxVertexNum];  
    Vertex S, V;  
    MGraph G = ReadG();  
  
    scanf("%d", &S);  
    ShortestDist( G, dist, path, S );  
  
    for ( V=0; V<G->Nv; V++ )  
        printf("%d ", dist[V]);  
    printf("\n");  
    for ( V=0; V<G->Nv; V++ )  
        printf("%d ", path[V]);  
    printf("\n");  
  
    return 0;  
}  
  
MGraph ReadG()  
{  
    int i,j;  
    int w,v,x;  
    MGraph p;  
    p=(PtrToGNode)malloc(sizeof(struct GNode));  
    scanf("%d%d",&w,&v);  
    p->Nv=w,p->Ne=v; 
    for(i=0;i<p->Nv;i++)
        for(j=0;j<p->Nv;j++)
       p->G[i][j]=INFINITY; 
    for(i=0;i<p->Ne;i++){  
        scanf("%d%d%d",&w,&v,&x);  
        p->G[w][v]=x;  
    }  
    return p;  
}  
  
void ShortestDist( MGraph Graph, int dist[], int count[], Vertex S )  
{  
    bool visit[MaxVertexNum];  
    int i;   
      
    /*初始化 */  
    for(i=0;i<Graph->Nv;i++){  
        dist[i]=INFINITY; /*dist[i]代表从S到i的最短距离 */  
        count[i]=0; /* count[i]代表从S到i的最短路径条数 */  
        visit[i]=false; /* 是否访问过该结点 */  
    }  
    dist[S]=0;  
    count[S]=1;
    /*第一次dijikstra，计算最短路径*/   
      
    while(1){  
        int min=INFINITY;  
        int v=-1;  
        /*得到最小的dist,将v点加入结果，求得从S到v的最短路径dist[v]*/   
        for(i=0;i<Graph->Nv;i++){  
            if(!visit[i]){  
                if(dist[i]<min){  
                    min=dist[i];  
                    v=i;  
                }  
            }  
        }  
        /*找不到最小的dist，跳出循环*/   
        if(v==-1)break;  
        visit[v]=true;  
        /*扫描v的所有邻接点，如果经过v到其邻接点的距离比已有距离更短，更新最短距离*/   
        for(i=0;i<Graph->Nv;i++){  
            if(!visit[i]&&Graph->G[v][i]!=INFINITY){  
                if(dist[v]+Graph->G[v][i]<dist[i]){  
                    dist[i]=dist[v]+Graph->G[v][i];
                    count[i]=count[v];  
                }     
                else if(dist[i]==dist[v]+Graph->G[v][i])
                    count[i]+=count[v];
            }  
        }     
    }  
    for(i=0;i<Graph->Nv;i++){
        if(dist[i]==INFINITY) dist[i]=-1;
    }
      
   
}   