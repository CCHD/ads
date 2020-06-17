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


//MGraph ReadG(); /* details omitted */


void ShortestDist( MGraph Graph, int dist[], int count[], Vertex S );


int main()
{
    int dist[MaxVertexNum], count[MaxVertexNum];
    Vertex S, V;
    int i,j;
    MGraph G1 = (MGraph*)malloc(sizeof(struct GNode));
    for(i=0;i<MaxVertexNum;i++)
    for(j=0;j<MaxVertexNum;j++)
    G1->G[i][j]=INFINITY;
    G1->G[3][0]=40;
    G1->G[3][1]=20;
    G1->G[3][2]=100;
    G1->G[3][7]=70;
    G1->G[0][4]=5;
    G1->G[0][7]=10;
    G1->G[4][7]=5;
    G1->G[6][2]=1; 
    G1->G[7][2]=50;
    G1->G[7][5]=3;
    G1->G[1][7]=30;   
    G1->Nv=8;
    G1->Ne=11;
    scanf("%d", &S);
    ShortestDist( G1, dist, count, S );
    for ( V=0; V<G1->Nv; V++ )
        printf("%d ", dist[V]);
    printf("\n");
    for ( V=0; V<G1->Nv; V++ )
        printf("%d ", count[V]);
    printf("\n");


    return 0;
}
void ShortestDist( MGraph Graph, int dist[], int path[], Vertex S )
{
    int i,j;
    int visit[MaxVertexNum];
    int PathLen[MaxVertexNum];
    for(i=0;i<MaxVertexNum;i++)
    {
        dist[i]=INFINITY;
        PathLen[i]=INFINITY;
        visit[i]=-1;
    }
    dist[S]=0;
    path[S]=-1;
//  PathLen[S]=-1;
    while(1)
    {
        int min=INFINITY;
        int v=-1;
        for(i=0;i<Graph->Nv;i++)
        {  
            if(visit[i]==-1)
            {  
                if(dist[i]<min)
                {  
                    min=dist[i];  
                    v=i;  
                }  
            }  
        }   
        if(v==-1)
            break;  
        visit[v]=1;
        for(j=0;j<Graph->Nv;j++)
        {
            if(Graph->G[v][j]!=INFINITY)
            {
                if(dist[j] > Graph->G[v][j] + dist[v])
                {
                    dist[j]=Graph->G[v][j]+dist[v];
                    PathLen[j]=PathLen[v]+1;
                    path[j]=v;
                }
                else if(dist[j]==Graph->G[v][j] + dist[v])
                {
                    if(PathLen[j]>=PathLen[v]+1)
                    {
                        PathLen[j]=PathLen[v]+1;
                        path[j]=v;
                    }
                }   
            }
        }
    }
    for(i=0;i<Graph->Nv;i++)
        if(dist[i]==INFINITY)
        {
            dist[i]=-1;
            path[i]=-1;
        }
}
