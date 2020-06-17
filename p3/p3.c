#include "stdio.h"
#include "stdlib.h"
#include "time.h"

#ifndef CLK_PER_SEC
#define CLK_PER_SEC 1800
#endif

#define SIZE 500000					//size for vertices
#define eSIZE 1100000					//size for edges
#define EMP -1						//mark for guard node
#define DEL -2						//mark dor deleted node
#define NAN 2147483647					//mark for infinity

int eStart[eSIZE+2];					//starts of edges
int eTerminal[eSIZE+2];					//terminals of edges
int eWeight[eSIZE+2];					//weights of edges
int eSearch[SIZE+2];					//edges sort by starts

typedef struct{						//a node of Fib-heap
	int parent, 					//parent node
	    left, 					//left brother node
	    right, 					//right brother node
	    son;					//one of its sons
	int mark;					//consolidate mark
	int key;					//its key
}FH_node;						//end of definision

FH_node FH[SIZE+2];					//a fib-heap

int FHmin;						//minium of root nodes of fib-heap

int NH[SIZE+2];						//a normal heap
int NHkey[SIZE+2];					//keys of this heap
int NHsearch[SIZE+2];					//where a vertice is in heap
int NHsize;						//now nodes in heap

int n,e;						//how many vertices and edges

int dij_res[SIZE];

void NH_build(int n){					//to build a normal heap
	int i;
	for (i=0;i<n;i++){
		NH[i]=i;				//initiate
		NHkey[i]=NAN;				//in the start all nodes have a key of infinite
		NHsearch[i]=i;				//in the start all nodes are sorted by there number
	}
	NHsize=n;					//in the start all nodes are in the heap
}

int NH_getmin(){
	return NH[0];					//return which node is the minium
}

int NH_exmin(){						//extract minium of a normal heap
	int b=NH[0],bval=NHkey[b],i=0,k,val,j,temp;
	NHsize--;					//one node is extracted
	NH[0]=NH[NHsize];				//exchange to the last node
	NHsearch[NH[0]]=0;				//exchange ended
	NHsearch[b]=EMP;				//make it not searched
	NH[NHsize]=NAN;					//make it empty
	k=NH[0];					//ready to sift down
	val=NHkey[NH[0]];				//save the value when have sifted down
	while (i*2+1<NHsize){				//not leaf
		j=i*2+1;				//left leaf
		if (j!=(NHsize-1)&&NHkey[NH[j+1]]<NHkey[NH[j]]) j++;		//if right leaf is smaller
		if (val<NHkey[NH[j]]) break;		//sifting down end
		NH[i]=NH[j];				//move smaller elements up
		NHsearch[NH[i]]=i;			//moving end
		i=j;					//iterate
	}
	NH[i]=k;					//save the node in the right situation
	NHsearch[k]=i;					//make it searched
	return bval;					//return the backed extracted minium value
}

int NH_decrease(int x, int k){				//decrease a node
	int i=NHsearch[x],j;
	while (i>0){					//not root
		j=(i-1)/2;				//parent
		if (NHkey[NH[j]]<k) break;		//sifting up end
		NH[i]=NH[j];				//moving down bigger elements
		NHsearch[NH[i]]=i;			//moving end
		i=j;					//iterate
	}
	NH[i]=x;					//put it in the right situation
	NHkey[x]=k;					//decrease
	NHsearch[x]=i;					//make it searched
	return 0;
}
 

int FH_build(int n){					//build a fib-heap
	int i;
	FH[0].left=n-1;					//left brother of the first node is the last node
	FH[0].right=1;
	FH[0].parent=FH[0].son=EMP;			//link in root
	FH[0].mark=0;					//not having lost a child
	FH[0].key=NAN;					//at first make it infinite
	FH[0].son=EMP;					//not having child
	for (i=1;i<n;i++){				//join in every node
		FH[i].left=i-1;				//link with its l-brother
		FH[i].right=i+1;			//link with its r-brother
		FH[i].parent=FH[i].son=EMP;		//not having a parent or a son
		FH[0].mark=0;				//not having lost a child
		FH[i].key=NAN;				//at first having infinite key value
	}
	FH[n-1].right=0;				//right brother of the last node is the first node
	FHmin=0;					//at first every node is the same
}

void FH_monolinkin(int x){				//link a node to the list
	int r=FH[FHmin].right;				//r is the right brother of minium
	FH[FHmin].right=x;				//link minium and x
	FH[x].left=FHmin;
	FH[r].left=x;					//link x and r
	FH[x].right=r;
	FH[x].parent=FH[x].son=EMP;			//make it not having son or parent
	if (FH[x].key<FH[FHmin].key)			//renew min
		FHmin=x;
}

void FH_multilinkin(int x){				//link a part of a circle list to the root
	int i,r=FH[FHmin].right,n=FH[x].right;		//at first:min---r,x---n
	FH[FHmin].right=n;				//min---n
	FH[n].left=FHmin;
	FH[x].right=r;					///x---r, at end min---n---x---r
	FH[r].left=x;
	i=n;
	while (i!=r){
		FH[i].parent=EMP;			//make every node not having parent or child
		i=FH[i].right;				//iterate
	}
}

void FH_cut(int x){					//cut a node off
	FH_node *p=&FH[x];				//easier to calculate
	if (p->parent==EMP) return; 			//itself is root
	if (p->right==x){				//not having a brother
		FH[p->parent].son=EMP;			//cut with parent
	}
	else {						//having a brother
		FH[p->parent].son=p->right;		//another brother represent sons
		FH[p->right].left=p->left;		//cut with brothers
		FH[p->left].right=p->right;
	}
	if (p->son!=EMP) {
		FH_multilinkin(p->son);			//link its sons to root
	}

}

void FH_decrease(int x, int k){				//decrease node in fib-heap
	FH_node *p=&FH[x];				//easier for calculate
	int i=x,next;
	p->key=k;					//decrease
	if (p->parent==EMP){				//it's already in root
		if (p->key<FH[FHmin].key) FHmin=x;	//renew minium
		return;
	}
	if (p->key>=FH[p->parent].key) return;		//not breaking rules of heap
	do {
		next=FH[i].parent;			//iterate to its parent
		FH[i].mark=0;				//moving to root
		FH_cut(i);				//cut off
		FH_monolinkin(i);			//link in root
		i=next;					//iterate
	}while (FH[i].mark!=0&&FH[i].parent!=EMP);	//while mark==1
	FH[i].mark=1;					//having lost a child
}

int FH_unite(int x, int y){				//unite y to x, useful in FH_exmin
	int l,r;
	l=FH[y].left;
	r=FH[y].right;
	if (y!=r){
		FH[l].right=r;
		FH[r].left=l;				//cut off from root	
	}
	if (FH[x].son==EMP){				//if x don't have child
		FH[y].parent=x;
		FH[x].son=y;
		FH[y].left=FH[y].right=y;
	}
	else {						//x have child
		FH[y].parent=x;				//link it to x
		l=FH[x].son;
		r=FH[l].right;
		FH[l].right=y;				//link it with their brothers
		FH[y].left=l;
		FH[y].right=r;
		FH[r].left=y;
	}
}

int FH_exmin(){						//extract min from
	int i=FH[FHmin].right,j,x,u,y,k,o,pre,nex,ret=FHmin;
	if (FH[FHmin].right==FHmin) {			//root is unique
		i=FH[FHmin].son;
		if (i==EMP) return FHmin;		//only one node
		x=i;					//make its sons root
		o=i;
		do {
			FH[i].parent=EMP;		//root shouldn't have parent
		}while (i!=x);
		FHmin=o;				//min will be renewed so arbitrary node is well
		x=FH[i].left;				//end of iterate
		goto special;				//special condition
	}
	if (FH[FHmin].son!=EMP) FH_multilinkin(FH[FHmin].son);			//link sons to root
	FH[FH[FHmin].right].left=FH[FHmin].left;	//cut off from root
	FH[FH[FHmin].left].right=FH[FHmin].right;
	static int ini=0, d[SIZE+2],storage[SIZE+1];	//to save time, or algorithm will be multipied O(n)
	if (ini==0) {					//not initialiazed
		for (int tmp=0;tmp<=SIZE+1;tmp++) d[tmp]=EMP;			//initialize,O(n),only once
		ini++;					//initialized
	}
	x=FH[i].left;					//end of itetare
special:;						//special condition jumps here!
	do{						//for every root
		k=0;					//counter for degree
		FH[i].parent=EMP;
		pre=i;
		nex=FH[i].right;			//iterate before extracting
		j=y=FH[i].son;
		if (j==EMP){				//without child
			k=0;
		}
		else {
			do{				//calculating children
				k++;
				j=FH[j].right;		//iterate
			}while (j!=y);			//iterating end

		}
		while (d[k]!=EMP){			//same degree
			o=d[k];
			if (FH[i].key>FH[o].key){	//i is smaller element
				int tmp=i;		//exchange
				i=o;
				o=tmp;		
			}
			FH_unite(i,o);			//unite them if degree is the same
			d[k]=EMP;
			k++;				//degree increase by 1
		}
		d[k]=i;					//store the node with degree k
		storage[i]=k;				//to recover initialized status with all value -1
		i=nex;					//iterate
	}while(pre!=x);
	i=x=FHmin=d[k];					//renew min
	do {
		if (FH[FHmin].key>FH[i].key) 
			FHmin=i;			//renew min
		d[storage[i]]=EMP;			//recover initialized status
		i=FH[i].right;				//iterate
	}while (i!=x);					//iterate end
	FH[ret].parent=DEL;				//deleted, but values are still here
	return ret;					//return extracted node
}

int FH_dijkstra(int s, int t){
	int i,x,j;
	FH_build(n);					//build fib-heap
	x=s;
	dij_res[s]=0;
	for (i=eSearch[x];i<eSearch[x+1];i++){		//first, tackle edges start with s
		FH_decrease(eTerminal[i],eWeight[i]);	//path extract
	}
	for (i=0;i<n-2;i++){				//greedy algorithm
		x=FH_exmin();				//get minium from heap
		dij_res[x]=FH[x].key;
		if (x==t) return FH[x].key;		//t is calculated, calculation ends
		for (j=eSearch[x];j<eSearch[x+1];j++){	//for every edge start in this node
			if (FH[eTerminal[j]].parent!=DEL&&FH[eTerminal[j]].key>FH[x].key+eWeight[j]&&eTerminal[j]!=s){
				FH_decrease(eTerminal[j],FH[x].key+eWeight[j]);		//path extract
			}
		}
	}
	dij_res[FHmin]=FH[FHmin].key;
	return FH[FHmin].key;				//the farthest node
}

int NH_dijkstra(int s, int t){
	int i,x,j,val;
	NH_build(n);					//build normal heap
	dij_res[s]=0;
	for (i=eSearch[s];i<eSearch[s+1];i++){		//first, tackle edges start with s
		NH_decrease(eTerminal[i],eWeight[i]);	//path extract
	}
	for (i=0;i<n-2;i++){				//greedy algorithm
		x=NH_getmin();
		val=NH_exmin();				//get minium from heap
		dij_res[x]=val;
		if (x==t) return val;			//t is calculated, calculation ends
		for (j=eSearch[x];j<eSearch[x+1];j++){	//for every edge start in this node
			if (NHkey[eTerminal[j]]>val+eWeight[j]&&eTerminal[j]!=s&&NHsearch[eTerminal[j]]!=EMP){
				NH_decrease(eTerminal[j],val+eWeight[j]);		//path extract
			}
		}
	}
	dij_res[NH[0]]=NHkey[NH[0]];
	return NHkey[NH[0]];				//the farthest node
}

int edge_comp(const void* a,const void* b){
	int s=*(int*)a,t=*(int*)b;
	if (eStart[s]==eStart[t]) return eTerminal[s]-eTerminal[t];
	else return eStart[s]-eStart[t];
}

int main(){
	int p=0,i,q,s,t,w,queries[SIZE],compare,sorts[eSIZE];
	int *tempS,*tempT,*tempW;
	char c;
	FILE *gr, *ss, *res;//gr for graph input,ss for problem source
	time_t start,stop;
	double timeF=0,timeN=0;
	int ri, repeats;

							//initiate
	printf("How many time do you want to repeats? :");
	scanf("%d",&repeats);
	gr=fopen("xx.txt", "r");
	ss=fopen("1000.ss", "r");
	while (1){
		if (fscanf(gr,"%c",&c)==0) break;
		if (c=='c'){				//comments
			while (c!=10) c=fgetc(gr);//\n
			continue;
		}
		if (c=='p'){				//describe the graph
			fscanf(gr, " sp %d %d",&n,&e);
		}
		if (c=='a'){
			fscanf(gr, "%d %d %d", &s, &t, &w);
			s--;				//file start on num 1 while we start on 0
			t--;
			eStart[p]=s;			//input an edge
			eTerminal[p]=t;
			eWeight[p++]=w;
			if (p==e) break;
		}
	}
	fclose(gr);					//close the file
	p=0;
	while (1){
		if (fscanf(ss,"%c",&c)==0) break;
		if (c=='c'){
			while (c!=10) c=fgetc(ss);	//comments
			continue;
		}
		if (c=='p'){
			fscanf(ss," aux sp ss %d",&q);	//describe the graph
		}
		if (c=='s'){
			fscanf(ss,"%d",&queries[p]);	//input queries
			queries[p]--;			
			p++;
			if (p==q) break;
		}
	}
	p=0;
	for (i=0;i<e;i++) sorts[i]=i;
	qsort(sorts,e,sizeof(int),edge_comp);		//sort edges by starts
	tempS=malloc(e*sizeof(int));			//make edges at their right situation
	tempT=malloc(e*sizeof(int));
	tempW=malloc(e*sizeof(int));
	for (i=0;i<e;i++){
		tempS[i]=eStart[sorts[i]];		//put right order in temporary memory
		tempT[i]=eTerminal[sorts[i]];
		tempW[i]=eWeight[sorts[i]];
	}
	for (i=0;i<e;i++){				//input right order from temporary memory
		eStart[i]=tempS[i];
		eTerminal[i]=tempT[i];
		eWeight[i]=tempW[i];
	}
	free(tempS);					//free temporary memory
	free(tempT);
	free(tempW);
	for (i=0;i<n;i++){				//get
		while (eStart[p]<i) p++;
		eSearch[i]=p;	
	}
	eSearch[n]=e;
	for (compare=0;compare<2;compare++){		//run twice
		if (compare){				//FIB-heap
			//res=fopen("res-fib","w");
			printf("FibH:\n");
			for (i=0;i<q;i++){
				start=clock();		//count start
				for (ri=0;ri<repeats;ri++) FH_dijkstra(queries[i],queries[i]);
				stop=clock();		//count stop
				timeF+=(double)(stop-start)/CLOCKS_PER_SEC;
				if(i%100==0) printf("%d/%d\n",i,q);
				/*for (int j=0;j<n;j++)
					fprintf(res,"%d ",dij_res[j]);
				fprintf(res,"%c",10);*/
			}
		}
		else {
			//res=fopen("res-nhp","w");	//normal heap
			printf("NH:\n");
			for (i=0;i<q;i++){
				start=clock();		//count start
				for (ri=0;ri<repeats;ri++) NH_dijkstra(queries[i],queries[i]);
				stop=clock();		//count stop
				timeN+=(double)(stop-start)/CLOCKS_PER_SEC;
				if(i%100==0) printf("%d/%d\n",i,q);
				/*for (int j=0;j<n;j++)
					fprintf(res,"%d ",dij_res[j]);
				fprintf(res,"%c",10);*/
			}
		}
		//fclose(res);
	}
	printf("Time of Fib-heap:%.4lf%c",timeF,10);
	printf("Time of Normal heap:%.4lf%c",timeN,10);
}
