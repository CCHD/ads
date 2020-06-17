#include "stdio.h"
#include "math.h"
#include "stdlib.h"
#include <time.h>

#ifndef CLK_TCK
#define CLK_TCK 1000
#endif

#define N 10002			//max size
#define INF 32767		//infinite
#define NINF -32768		//negative infinite

clock_t  start, stop; 
double duration;
int Function(int l, int *v);
int main(){
	int i,j,l,v[N];
	srand(time(0));
	scanf("%d",&l);
	for(j=0;j<100;j++){
		for(i=0;i<l;i++){
	    	v[i]= rand()%20001-10000;
	    }
		start=clock();  //Cauculation Start
	    for(i=0;i<100;i++){
	
	    	Function(l,v);
		}
	    stop=clock();  //Cauculation End
	    duration=((double)(stop-start))/CLK_TCK;
	    printf("%f\n",duration);
	}
	
} 




int Function(int l, int* v){
	int pre[N],		//last element in ascending list
	nex[N],			//next element in descending list
	pre_length[N],		//length of an ascending list ends here
	nex_length[N],		//length of a descending list starts here
//	v[N],			//values
	pre_st[N],		//to continue a ascending list how big value must be
	nex_st[N],		//as above, for a descending list
	i,
//	l,			//total length
	peak,			//peak situation
	peakexists;		//if there exists a peak
//	scanf("%d",&l);
	for (i=0;i<=l;i++){	//initiate
		pre_st[i]=INF;	//lists are not calculated
		nex_st[i]=INF;
	}
//	for (i=0;i<l;i++){	//input data
//		scanf("%d",&v[i]);
//	}
	pre_st[0]=NINF;		//only empty list exists
	nex_st[0]=NINF;
	for (i=0;i<l;i++){
		int lp=0,rp=l,mp;
		while (rp-lp>1){	//search, get the longest list able to continue here
			mp=(lp+rp)/2;
			if (v[i]>pre_st[mp])
				lp=mp;
			else rp=mp;
		}
		pre_st[rp]=v[i];	//a lower-value list, more easy to continue
		pre_length[i]=rp;	//the length of the list
	}
	for (i=l-1;i>=0;i--){		//calculate from tail
		int lp=0,rp=l,mp;
		while (rp-lp>1){	//search, get the longest list able to continue here
			mp=(lp+rp)/2;
			if (v[i]>nex_st[mp])
				lp=mp;
			else rp=mp;
		}
		nex_st[rp]=v[i];	//a lower-value list, more easy to continue
		nex_length[i]=rp;	//the length of the list
	}
	peak=0;
	peakexists=0;
	for (i=1;i<l;i++){
		if (peakexists ==0 && pre_length[i]>1 && nex_length[i]>1) peakexists=1;
		if (pre_length[i]+nex_length[i]>=pre_length[peak]+nex_length[peak]
				&&pre_length[i]!=1	//not a descending list
				&&nex_length[i]!=1	//not an ascending list
				)
			peak=i;
		else if(pre_length[i]+nex_length[i]==pre_length[peak]+nex_length[peak]
				&&pre_length[i]!=1	//not a descending list
				&&nex_length[i]!=1	//not an ascending list
				){
			if(abs(pre_length[i]-nex_length[i])<abs(pre_length[peak]-nex_length[peak])) //the difference is smaller
				peak=i;
		}
	}
//	if (peakexists)//output
//		printf("%d %d %d\n",pre_length[peak]+nex_length[peak]-1,peak+1,v[peak]);
//	else 
//		printf("No peak shape\n");
}

