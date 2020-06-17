#include<stdio.h>
#include<stdlib.h>
void Insertion(int A[],int Tar[],int N);
void Heap(int A[],int Tar[],int N);
void Pecodown(int A[],int i,int N);
void Swap(int* a,int *b);
int main(){
	int N,i;
	int *A,*Tar;
	scanf("%d",&N);
	A=(int*)malloc(N*sizeof(int));
	Tar=(int*)malloc(N*sizeof(int));
	for(i=0;i<N;i++)
	    scanf("%d",&A[i]);
	for(i=0;i<N;i++)
	    scanf("%d",&Tar[i]);
	Insertion(A,Tar,N);
	return 0;
}
void Insertion(int A[],int Tar[],int N){
	int i,j,k;
	int tmp;
	int *T;
	T=(int*)malloc(N*sizeof(int));
	for(i=0;i<N;i++)
	   T[i]=A[i];
    for(i=1;i<N;i++){
       tmp=T[i];
       for(j=i;j>=0;j--){
           if(T[j-1]>tmp){
             T[j]=T[j-1];
           }
           else break;
       }
       T[j]=tmp;
    for(k=0;k<N;k++){
       if(T[k]!=Tar[k])
         break;
    }
    if(k<N) continue;
    else break;
}
    if(i<N-1){
      printf("Insertion Sort\n");
      i++;
      tmp=T[i];
      for(j=i;j>=0;j--)
          if(T[j-1]>tmp)
             T[j]=T[j-1];
          else break;
      T[j]=tmp;
      for(i=0;i<N;i++){
      if(!i)
      printf("%d",T[i]);
      else
      printf(" %d",T[i]);    
    }
    }
    else Heap(A,Tar,N);
    free(T);
}
void Heap(int A[],int Tar[],int N){
    int *T;
    int i,j;
    T=(int*)malloc(N*sizeof(int));
    for(i=0;i<N;i++)
        T[i]=A[i];
	for(i=N/2;i>=0;i--)
	   Pecodown(T,i,N);
	for(i=N-1;i>0;i--){
	    Swap(&T[0],&T[i]);
	    Pecodown(T,0,i);
        for(j=0;j<N;j++)
           if(T[j]!=Tar[j])
              break;
        if(j<N)  continue;
        else break;
	}
	if(i>0){
	  printf("Heap Sort\n");
	  i--;
	  Swap(&T[0],&T[i]);
	  Pecodown(T,0,i);
	  for(i=0;i<N;i++){
	     if(!i)
	     printf("%d",T[i]);
	     else 
	     printf(" %d",T[i]);
	  }
	}
	free(T);
}
void Pecodown(int A[],int i,int N){
	int child,leftchild;
	int tmp;
	for(tmp=A[i];(leftchild=2*i+1)<N;i=child){
	    child=leftchild;
	    if(child!=N-1&&A[child+1]>A[child]){
          child++;
	    }
	    if(tmp<A[child])
	       A[i]=A[child];
	    else break;
	}
	A[i]=tmp;
}
void Swap(int *a,int *b){
	int tmp;
	tmp=*a;
	*a=*b;
	*b=tmp;
}