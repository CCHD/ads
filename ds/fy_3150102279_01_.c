#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define Max 101
int weight[Max];
int parent[Max];
int num_child[Max];
int sum[Max];
int TreeNode[Max][Max];
int path[Max][Max];
int road=0;
void store(int pa);
void DFS(int a,int S);
void reverse(int x);
void Sort();
void Print();
int main(){
	int N,M,S;
	int i,j;
	scanf("%d %d %d",&N,&M,&S);
    for(i=0;i<N;i++)
    scanf("%d",&weight[i]);
    int unleaf,num,leaf;
    parent[0]=-1;
    for(i=0;i<M;i++){
        scanf("%d %d",&unleaf,&num);
        num_child[unleaf]=num;
        for(j=0;j<num;j++){
            scanf("%d",&leaf);
            TreeNode[unleaf][j]=leaf;
            parent[leaf]=unleaf;
        }
    }
    if(M==0){
       if(weight[0]==S) 
       {
       printf("%d",weight[0]);
       return 0;
       }
       else if(weight[0]<S) return 0;
   }
       memcpy(sum,weight,N*sizeof(int));
       DFS(0,S);
       Sort();
       return 0;

}
void DFS(int node,int S){
	int next,i;
	for(i=0;i<num_child[node];i++){
	   next=TreeNode[node][i];
	   sum[next]=sum[node]+weight[next];
	   if(sum[next]==S){
	   if(num_child[next]==0){
          store(next);
	   }
	   else continue;
	   }
	   else if(sum[next]<S)
	   DFS(next,S);
	   else continue;
	}
}
void Sort(){
	int i,j,k,cc;
	int min;
	for(k=1;k<road;k++){
	for(i=road-1;i>=k;i--){
       for(j=0;j<Max;j++){
       	  if(path[i][j]<path[i-1][j]){
            break;
          }
          else if(path[i][j]>path[i-1][j]){
       	  	for(cc=0;cc<Max;cc++){
       	  		min=path[i-1][cc];
       	  		path[i-1][cc]=path[i][cc];
       	  		path[i][cc]=min;
       	  	}
            break;
       	  }
       }
	}
}
  Print();
}
void store(int pa){
	int i=0;
	while(pa!=-1){
		path[road][i++]=weight[pa];
		pa=parent[pa];
	}
	road++;
	reverse(i);
}
void reverse(int x){
     int i,k,tmp,t;
     t=road-1;
     for(i=0,k=x-1;i<k;i++,k--){
         tmp=path[t][i];
         path[t][i]=path[t][k];
         path[t][k]=tmp;
     }
     
}
void Print(){
    int i,j=0;
    for(i=0;i<road;i++){
    	while(path[i][j]){
    		if(j==0)
    		printf("%d",path[i][j++]);
    	    else if(path[i][j+1]==0)
    		printf(" %d\n",path[i][j++]);
    	    else
    	    	printf(" %d",path[i][j++]);
    	}
    	j=0;
    }
}