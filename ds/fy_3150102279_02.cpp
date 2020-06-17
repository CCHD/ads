/*Author: Hu Danchun; ID:3150102279; N0.02*/
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

int FindRoot(int x);
void MergeSort(Way path[],int M);
void MSort(Way A[],Way tmp[],int left,int right);
void Merge(Way A[],Way tmp[],int lpos,int rpos,int rightend);
int main(){
	int N,M,i,j;
	int R1,R2;
	int count;
	int max_cost=0;
	scanf("%d%d",&N,&M);
	for(i=0;i<M;i++)
	   scanf("%d%d%d%d",&path[i].city1,&path[i].city2,&path[i].cost,&path[i].status);
    MergeSort(path,M);
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
void MergeSort(Way path[],int M){
	Way *tmp;
	tmp=(Way*)malloc(sizeof(path[0])*M);
	if(tmp!=NULL){
		MSort(path,tmp,0,M-1);
		free(tmp);
	}
	else
		printf("error!\n");
}
void MSort(Way A[],Way tmp[],int left,int right){
	int center;
	if(left<right){
		center=(left+right)/2;
		MSort(A,tmp,left,center);
		MSort(A,tmp,center+1,right);
		Merge(A,tmp,left,center+1,right);
	}
}
void Merge(Way A[],Way tmp[],int lpos,int rpos,int rightend){
	int i,leftend,num_element,tmp_pos;
	leftend=rpos-1;
	tmp_pos=lpos;
	num_element=rightend-lpos+1;
	while(lpos<=leftend&&rpos<=rightend){
		if(A[lpos].status>A[rpos].status)
			tmp[tmp_pos++]=A[lpos++];
		else if(A[lpos].status<A[rpos].status)
			tmp[tmp_pos++]=A[rpos++];
		else if(A[lpos].cost>A[rpos].cost)
			tmp[tmp_pos++]=A[rpos++];
		else tmp[tmp_pos++]=A[lpos++];
	}
	while(lpos<=leftend)
		tmp[tmp_pos++]=A[lpos++];
	while(rpos<=rightend)
		tmp[tmp_pos++]=A[rpos++];
	for(i=0;i<num_element;i++,rightend--)
		A[rightend]=tmp[rightend];

}