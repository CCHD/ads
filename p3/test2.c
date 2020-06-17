#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main(){
    srand((int)time(0));
	FILE *fp=fopen("xx.txt","w");
	int m,n;
	scanf("%d %d",&m,&n);
	fprintf(fp,"p sp %d %d\n",m,n);
	int x,y,z;
	int p=0;
	while(p<n/2){
		x=1+rand()%m;
		y=1+rand()%m;
		z=1+rand()%3000;
		fprintf(fp,"a %d %d %d\n",x,y,z);
		fprintf(fp,"a %d %d %d\n",y,x,z);
		p++;
	}
	fclose(fp);
	return 0;
}