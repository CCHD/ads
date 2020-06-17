#include <stdio.h>
#include <stdlib.h>
#define Infinity 0x7fffffff;
#define No_Road -1;
#define NotAVertex -1;

int Cmax;					/*the maximum capacity of each station*/
int Graph[501][501];		/*store the edge between Si and Sj*/
int N;						/*total number of stations*/
int Sp;						/*the index of the problem station*/
int C[501];					/*the current numer of bikes at Si*/
int dist[501];				/*the shortest distence from S0 to Si*/
int Visited[501];			/*if the station has been checked, Visited is 1*/
int Path[501];				/*store the temporary path*/
int Best[501];				/*store the best path*/
int minsend = Infinity;		/*number of bikes sent*/
int mintake = Infinity;		/*number of bikes taken back*/

void init();				/*initialize the Grah and get information of the Graph*/
void Dijkstra(int *visit);	/*figure out the shortest distence from S0 to each station*/
void DFS(int station, int distance, int send, int take, int num); /*search for the best path form S0 to Sp*/
void printf_path();			/*print answer as required*/

int main()
{
	int *visit;	

	init();
	visit = (int *)calloc(N+1, sizeof(int)); /*set all visit[i] as 0*/
	Dijkstra(visit);		/*get the shortest distence to Sp*/
	DFS(0, 0, 0, 0, 0);
	printf_path();
	free(visit);
	return 0;
}

void init()
{
	int M;
	int i, j;
	int Si, Sj, edge;
	scanf("%d %d %d %d", &Cmax, &N, &Sp, &M);
	for (i = 0; i <= N; i++)
		for (j = 0; j <= N; j++)
			Graph[i][j] = Graph[j][i] = No_Road; 
	/*Initialize the connectedness between the stations*/
	for (i = 1; i <= N; i++){
		scanf("%d", &C[i]);
		dist[i] = Infinity;
	}/*Input current number of bikes at each station and 
	initialize the shortest distence of each station*/
	for (i = 0; i < M; i++)
	{
		scanf("%d %d %d", &Si, &Sj, &edge);
		Graph[Si][Sj] = Graph[Sj][Si] = edge;
	}/*Input the connectedness between the stations*/
}

void Dijkstra(int *visit)
{
	int i, j, v, min;
	dist[0] = 0;
	for(i=0; i<=N; i++){
		v = -1;
		min = Infinity; /*Initialize the minimun*/
		for(j = 0; j<=N; j++){
			if(dist[j]<min && dist[j]>=0 && visit[j]==0){
				v = j;
				min = dist[j];
			}
		}/*Find out the shortest path hasn't been checked*/
		if(v == -1)
			break;
		visit[v] = 1; /* Sk has been checked*/
		for(j = 1; j<=N; j++){
			if (Graph[v][j] > 0) /*Sv and Sj are connected*/
				if(dist[j] > dist[v]+Graph[v][j])
					dist[j] = dist[v]+Graph[v][j];
		}/*update the shortest distence*/
	}
	return;
}

void DFS(int station, int distance, int send, int take, int num)
{
	int i, bikes;
	int new_send, new_take;
	if (distance > dist[Sp]) 
		return;
	/*return if the distance is already too big*/ 
	if (station == Sp && distance == dist[Sp]){
		/*find one of the shortest paths*/
		if (send < minsend || (send == minsend && take < mintake)){
			/*compare current path with the best path*/
			minsend = send;			/*update the minsend*/
			mintake = take;			/*update the mintake*/
			for (i = 0; i < num; i++)
				Best[i] = Path[i];	/*update the best path*/
		}
		return;
	}
	for (i = 1; i <= N; i++){
		if (Graph[station][i] > 0 && Visited[i] == 0){
			/*the number of bikes before any operations*/	
			new_send = send;
			/*calculate the number of bikes sent*/
			bikes = Cmax / 2 - C[i];
			new_take = take - bikes;
			/*calculate the number of bikes sent*/
			if (new_take < 0){
				new_send -= new_take;
				new_take = 0;
			}/*have to send bikes from PBMC*/
			Visited[i] = 1;	/*Si has been checked*/
			Path[num] = i;	/*store the station*/
			DFS(i, distance + Graph[station][i], new_send, new_take, num + 1);
			Visited[i] = 0; /*refresh the information*/
		}
	}
}

void printf_path()
{
	int i = 0;
	printf("%d ", minsend); 		/*Output the number of bikes sent*/
	printf("0");					/*Output So*/
	while(Best[i] != Sp)
		printf("->%d", Best[i++]); 	/*Output the best path between S0 and Sp*/
	printf("->%d %d", Sp, mintake); /*Output Sp and the number of bikes taken back*/
}