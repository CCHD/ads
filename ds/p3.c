#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct car{
	char plate[8];
	int time;
	int state;
	int cost_time;
};
int cmp1(const void* a,const void* b);
int cmp2(const void* a,const void* b);
int cmp3(const void* a,const void* b);
int main(){
	int n,k;
	int i;
	int hh,mm,ss;
	char in_out[4];
	scanf("%d%d",&n,&k);
	struct car *record;
	record=(struct car*)malloc(n*sizeof(struct car));
	for(i=0;i<n;i++){
	    scanf("%s%d:%d:%d%s",record[i].plate,&hh,&mm,&ss,in_out);
	    record[i].time=hh*3600+mm*60+ss;
	    if(in_out[0]=='i'){
	      record[i].state=0;
	    }
	    else record[i].state=1;
	    record[i].cost_time=0;
	}
	qsort(record,n,sizeof(record[0]),cmp1);
	int last=-1;
	for(i=0;i<n;i++){
	    if(!strcmp(record[i].plate,record[i+1].plate)&&record[i].state==0&&record[i+1].state==1&&i<n-1){
            if(last!=-1&&!strcmp(record[i].plate,record[last].plate)){
               record[i+1].cost_time=record[i+1].time-record[i].time+record[last].cost_time;
               record[last].cost_time=0;
            }
            else
               record[i+1].cost_time=record[i+1].time-record[i].time;
            i++;
            last=i;
	    }
	    else{
           record[i].state=-1;
	    }
	}
    int total=0,j=0;
    qsort(record,n,sizeof(record[0]),cmp2);
    for(i=0;i<k;i++){
        scanf("%d:%d:%d",&hh,&mm,&ss);
        ss+=hh*3600+mm*60;
        while(j<n&&record[j].time<=ss){
          if(record[j].state==0)
               total++;
          else if(record[j].state==1)
             total--;
         j++;
        }
        printf("%d\n",total);
    }
    qsort(record,n,sizeof(record[0]),cmp3);
    printf("%s ",record[0].plate);
    for(i=1;i<n;i++){
       if(record[i].cost_time!=record[0].cost_time)
          break;
       printf("%s ",record[i].plate);
    }
    printf("%02d:%02d:%02d\n",record[i-1].cost_time/3600,(record[i-1].cost_time/60)%60,record[i-1].cost_time%60);
}
int cmp1(const void* a,const void* b){
	if(!strcmp(((struct car*)a)->plate,((struct car*)b)->plate))
	return ((struct car*)a)->time-((struct car*)b)->time;
	else
	    return strcmp(((struct car*)a)->plate,((struct car*)b)->plate);
}
int cmp2(const void* a,const void* b){
	return ((struct car*)a)->time-((struct car*)b)->time;
}
int cmp3(const void* a,const void* b){
	if(((struct car*)a)->cost_time==((struct car*)b)->cost_time)
	   return strcmp(((struct car*)a)->plate,((struct car*)b)->plate);
	else 
	   return ((struct car*)b)->cost_time-((struct car*)a)->cost_time;
}
