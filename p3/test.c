#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

int main(){
	int i,j,n,p;
	srand(NULL);
	int *x;
	scanf("%d%d",&n,&p);  //n is the number of queries. p is the number of vertices.
	x=(int*)malloc(sizeof(int)*n);
	memset(x,0,sizeof(int)*n);
	FILE* fp=fopen("1000.ss","w");
	fprintf(fp,"c file contains %d queries\n",n);
	fprintf(fp,"p aux sp ss %d\n",n);
	for(i=0;i<n;i++){
		jump:x[i]=rand()%p;
		for(j=0;j<i;j++){
			if(x[i]==x[j])
				goto jump;
			else
				continue;
		}
		fprintf(fp,"s %d\n",x[i]+1);
	}
	return 0;
}