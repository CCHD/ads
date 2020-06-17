#include <stdio.h>
#include <math.h>
#define INIFINITY 10000000//Big enough
struct {
	int parent;//store parent
	int Col;//store different ways
	int send;//the number of sending bikes
	int back;//the number of back bikes
} path[1000][1000];//store all the shortest path


int C, N, sp, M, G[1000][1000], cur[1000];
int time[1000], known[1000], count[1000];


void findpath(int x);//find the shortest ways
					 //ps:not the suitable way


int main(void){
	int v, w, i, j, k, l;
    int way[1000];//store the demanding way
	int send, back, pre, prep;
	scanf("%d%d%d%d", &C, &N, &sp, &M);//get the Capacity of each station,the number of stations,the problem station,the number of edge
	for (i = 1; i <= N; i++) {
		scanf("%d", &cur[i]);//the sums of bikes of each station
		time[i] = -1;  
		known[i] = 0;
		count[i] = 0;//initialnize 1
	}
	//initialnize 2
	for (i = 1; i <= N; i++){
		for (j = 1; j <= N; j++) {
			G[i][j] = 0;
			path[i][j].parent = path[i][j].Col = 0;
			path[i][j].send = path[i][j].back = 0;
		}
	}//initialnize 3
	for (i = 0; i < M; i++) {
		scanf("%d %d %d", &v, &w, &j);
		G[w][v] = G[v][w] = j;
	}//store the edges
	
	findpath(sp);//find the shortest path
	
	//following: find the best way from the shortest ways
	send = back = INIFINITY; //Big enough
	for (i = 0; i < count[sp]; i++) {
		if (send > path[sp][i].send ||(send == path[sp][i].send && back > path[sp][i].back)) {
			send = path[sp][i].send;
			back = path[sp][i].back;
			pre = path[sp][i].parent;
			prep = path[sp][i].Col;
		}
	}
	for (i = pre, j = prep, k = 0; i >= 0; ) {
		way[k++] = i;
		pre = path[i][j].parent;
		prep = path[i][j].Col;
		i = pre;
		j = prep;
	}
	//above: to find out the best way accoding the the number of back bikes and send bikes
    //following: print the ways and the send bikes number and the back bikes number
	printf("%d ", send);
	for (--k; k >= 0; k--)
	printf("%d->", way[k]);
	printf("%d %d\n", sp, back);
	return 0;
}


void findpath(int x)
{
	int v, w, i, j, k, len, temp;
	//initialnize 4 : initialnize the start
	time[0] = 0;
	path[0][0].parent = -1;
	path[0][0].Col = -1;
	path[0][0].send = path[0][0].back = 0;
	count[0] = 1;
	//find the index of minimum time
	while (!known[x]) {
		len = INIFINITY;
		for (i = 0; i <= N; i++) {
			if (known[i])
				continue;
			if (time[i] >= 0 && time[i] < len) {
				len = time[i];
				v = i;
			}
		}
		//mark it as known
		known[v] = 1;
		//find time waving ways
		for (w = 1; w <= N; w++) {
			if (!G[v][w] || known[w])//if two station are not connected or the station already know ,do nothing
				continue;
			if (time[w] >= 0 && time[w] < time[v] + G[v][w])//if time>0 and time is shorter ,don't do anything 
				continue;
			else if (time[w] == -1 || time[w] >= time[v] + G[v][w]) {
					if (time[w] == -1 || time[w] > time[v] + G[v][w]) //if time==-1(means this is the first way),or time is longer ,setcount[w]==0
						count[w] = 0;
					time[w] = time[v] + G[v][w];//update the time 
					temp = fabs(cur[w] - C/2);
					for (i = 0, j = count[w]; i < count[v]; i++, j++) {
						path[w][j].parent = v;
						path[w][j].Col = i;//record the path (parent if path[parent][Col])
						//caculate the needing changes of bike bumber
						if (cur[w] >= C/2) {
							path[w][j].back = path[v][i].back + temp;
							path[w][j].send = path[v][i].send;
						}
						else {
							if (temp <= path[v][i].back) {
								path[w][j].back = path[v][i].back - temp;
								path[w][j].send = path[v][i].send;
							}
							else {
								path[w][j].send = path[v][i].send + temp - path[v][i].back;
								path[w][j].back = 0;
							}
						}
					}
					count[w] = j;//record the kinds of ways
			}
		}
	}
}