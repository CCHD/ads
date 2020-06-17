#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define Max 124750
#define INFINITY 0x7fffffff

typedef struct edge{
	int city1;
	int city2;
	int cost;
	int status;
}Way;
Way path[Max];

int Root[Max];
int cost[Max];

int cmp(const void *a,const void *b);
int FindRoot(int x);

int main(){
	int N,M,i,j;
	int R1,R2;
	int count;
	int max_cost=0;
	scanf("%d%d",&N,&M);
	for(i=0;i<M;i++)
	   scanf("%d%d%d%d",&path[i].city1,&path[i].city2,&path[i].cost,&path[i].status);
	qsort(path,M,sizeof(path[0]),cmp);
	for(i=1;i<=N;i++){
	    count=1;
	    cost[i]=0;
        memset(Root,0,(N+1)*sizeof(Root[0]));
	    for(j=0;j<M&&count!=N-1;j++){
	        if(path[j].city1==i||path[j].city2==i)
	           continue;
            R1=FindRoot(path[j].city1);
            R2=FindRoot(path[j].city2);
            if(R1==R2)
               continue;
            Root[R1]=R2;
            count++;
            if(!path[j].status)
               cost[i]+=path[j].cost;
	    }
	    if(count!=N-1)
	       cost[i]=INFINITY;
	    if(cost[i]>max_cost)
	       max_cost=cost[i];
    }
	if(max_cost==0)
	   printf("0\n");
	else{
	    int flag=1;
	    for(i=1;i<=N;i++)
	        if(cost[i]==max_cost){
	           if(flag){
	              flag=0;
	              printf("%d",i);
	           }
	           else
	               printf(" %d",i);
	        }
	}
	return 0;
}

int FindRoot(int x){
	if(!Root[x]) return x;
	else return Root[x]=FindRoot(Root[x]);
}

int cmp(const void *a,const void *b){
	if(((Way*)a)->status==((Way*)b)->status)
	   return ((Way*)a)->cost - ((Way*)b)->cost;
	return ((Way*)b)->status - ((Way*)a)->status;
}