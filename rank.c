#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define true 1
#define false 0
#define INF 0x7fffffff

struct problem{
	char name[21];
	int first;
	int debug;
	int accept;
}pro[9];

int *final_order; //the result order
int final_finished; //the number of accepted pros
int final_time;
int *try_order;

void dfs(int num,int t0,int total_time,int N,int H);
void update(int num,int total_time);
int main(){
	
	int H,N,t0;//H is the competition time, N is the number of problems, t0 is the seeing time
	int i;
	scanf("%d",&H);
	while(H>=0){
		scanf("%d%d",&N,&t0);

		final_order=(int*)malloc(sizeof(int)*N);
		try_order=(int*)malloc(sizeof(int)*N);

		memset(final_order,0,sizeof(final_order));
		memset(try_order,0,sizeof(try_order));

		for(i=0;i<N;i++){
			scanf("%s%d%d",pro[i].name,&pro[i].first,&pro[i].debug);
			pro[i].accept=false;
		}
		//in the beginning, the number of finished problems is 0,
		//final_time is set to be the largest interger
		final_finished=0;
		final_time=INF;
		//initialize

		for(i=0;i<N;i++){
			pro[i].accept=true;
			try_order[0]=i;
			dfs(0,t0,0,N,H);
			pro[i].accept=false;
		}
		
		printf("Total Time = %d\n",final_time);
		for(i=0;i<final_finished;i++)
			printf("%s\n",pro[final_order[i]].name);
		scanf("%d",&H);
	}
}
void dfs(int num,int used_time,int total_time,int N,int H){
	int i;
	int first_submit_time=used_time+pro[try_order[num]].first;
	//the times of debugging
	int detimes=(first_submit_time-1)/60;
	//total time until accepted
	int next_time=first_submit_time+pro[try_order[num]].debug*detimes;
	//add the punishment time
	int next_total_time=next_time+total_time+detimes*20;
	//if can submit the right answer in the competition time
	if(next_time<=H*60){
		num++;//num is the number of finished problems
		if(num<N){//not complete all the problems
			for(i=0;i<N;i++){
				if(!pro[i].accept){
					pro[i].accept=true;
					try_order[num]=i;
					dfs(num,next_time,next_total_time,N,H);
					pro[i].accept=false;
				}
			}
		}
		else update(num,next_total_time);
	}
	//solve the current problem, but out of time
	else update(num,total_time);
}

void update(int num,int total_time){
	if(num<final_finished) return;
	if(num==final_finished&&total_time>=final_time)
		return;
	final_finished=num;
	final_time=total_time;
	for(int i=0;i<num;i++){
		final_order[i]=try_order[i];
	}
}