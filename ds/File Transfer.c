#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef int Disjoint;
Disjoint *Set;
int N,count;
void Union(int num_com1,int num_com2);
int check(int num_com1,int num_com2);
int Com(int N,Disjoint *Set);
int Find(int a,Disjoint *Set);
int main(){
	int i,j,flag=0; 
	int num_com1,num_com2,Iscon;
	scanf("%d",&N);
    count=N;
	Set=(Disjoint*)malloc(sizeof(Disjoint)*(N+1));
	for(i=0;i<=N;i++)
	Set[i]=0;
	char x;
	while((x=getchar())!='S'){
	scanf("%d%d",&num_com1,&num_com2);
    if(x=='C'){
    Iscon=check(num_com1,num_com2);
    if(Iscon) printf("yes\n");
    else printf("no\n");
    }
    else if(x=='I')
    Union(num_com1,num_com2);
	}
    if(count==1) printf("The network is connected.");
    else printf("There are %d components.",count);
    return 0;
}
void Union(int num_com1,int num_com2){
    int root1,root2;
	root1=Find(num_com1,Set);
    root2=Find(num_com2,Set);
    if(root1!=root2){
	Set[root1]=root2;
    count--;
	}
}
int check(int num_com1,int num_com2){
	if(Find(num_com1,Set)==Find(num_com2,Set)) return 1;
	return 0;
}
int Find(int a,Disjoint *Set){
    if(Set[a]==0) return a;
    else
    return Set[a]=Find(Set[a],Set);
}
