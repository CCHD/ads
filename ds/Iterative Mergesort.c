#include <stdio.h>

#define ElementType int
#define MAXN 100

void merge_pass( ElementType list[], ElementType sorted[], int N, int length );

void output( ElementType list[], int N )
{
    int i;
    for (i=0; i<N; i++) printf("%d ", list[i]);
    printf("\n");
}

void  merge_sort( ElementType list[],  int N )
{
    ElementType extra[MAXN];  /* the extra space required */
    int  length = 1;  /* current length of sublist being merged */
    while( length < N ) { 
        merge_pass( list, extra, N, length ); /* merge list into extra */
        output( extra, N );
        length *= 2;
        merge_pass( extra, list, N, length ); /* merge extra back to list */
        output( list, N );
        length *= 2;
    }
} 


int main()
{
    int N, i;
    ElementType A[MAXN];

    scanf("%d", &N);
    for (i=0; i<N; i++) scanf("%d", &A[i]);
    merge_sort(A, N);
    output(A, N);

    return 0;
}

void merge_pass( ElementType list[], ElementType sorted[], int N, int length ){
	int l1,l2,r1,r2;
	int i,j,tmp;
	l1=0;
	r1=l1+length-1;
	l2=l1+length;
	r2=l2+length-1;
	while(r1<N&&r2<N){
	      i=l1,j=l2;
	      tmp=i;
	      while(i<=r1&&j<=r2){
	      if(list[i]>list[j]){
	         sorted[tmp++]=list[j++];
	      }
	      else sorted[tmp++]=list[i++];
          }
          while(i<=r1)
                sorted[tmp++]=list[i++];
          while(j<=r2)
                sorted[tmp++]=list[j++];
          l1=r2+1;
          l2=l1+length;
          r1=l1+length-1;
          r2=l2+length-1;
	}
	if(r1>=N-1){
		    tmp=l1;
	   while(l1<N)
	        sorted[tmp++]=list[l1++];
	}
	else{
		 i=l1,j=l2;
		 tmp=i;
		 while(i<=r1&&j<N){
		 if(list[i]>list[j])
		 	sorted[tmp++]=list[j++];
		 else
		 	sorted[tmp++]=list[i++];
	}
	    while(i<=r1)
	    	sorted[tmp++]=list[i++];
	    while(j<N)
	    	sorted[tmp++]=list[j++];
}
}
