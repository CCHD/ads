#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define INFINITY 240000  //a mark of the time
#define MAX_SIZE 10000  //maxumim size of the record array
 
typedef struct Cars_node Cars; 
struct Cars_node {     //the struct to store each record of cars
	char plate[8];   // the plate number
	int time_in;     
	int time_out;
	int total_time;
};
int number;        //the number of the valid records
int n, k;           //the number of record and the times of query
Cars car[MAX_SIZE];     //to read all the records
Cars valid_car[MAX_SIZE];    //to store the valid records

void Initialize_cars();    
void Load_record();        //the function to load all the records
void Timeofcars();         //the function to calculate the total time of each cars
void Valid_record();       //to sort out the valid records
int timetransform(int hour, int min, int sec);   //to transform time into second
int cmp(const void *a, const void *b);   // to compare two struct 

int main()
{
	int i;           //the loop variable
	int j;
	int qtime;      //the time that querys
	int maxtime;      //the maximum time of the cars
	int hour, min, sec;  //the time
	int count = 0;        //to count the number of cars in a specific time 
	char *name[10000];
	scanf("%d", &n);
	scanf("%d", &k);

	Initialize_cars();  //initialize the array,and load the records
	Load_record();
	Valid_record();

	for (i = 0; i <k; i++)   //k times of query
	{
		scanf("%d:%d:%d", &hour, &min, &sec);  //read the time
		qtime = timetransform(hour, min, sec);  //calculate the time
		for (j = 0; j < number; j++)    //to find how many cars are in, at this moment
			if (((valid_car[j].time_in) <= qtime) && (valid_car[j].time_out > qtime)) //to judge 
				count++;  //a car found
		printf("%d\n", count);  //all records visited, output the count
		count = 0;             //before next query, reset count
	}
	Timeofcars();             // calculate the total time of each car
	qsort(valid_car, number, sizeof(Cars), cmp); //sort those cars 
	maxtime = valid_car[0].total_time;              //the car of longest time is at the first position
	for (i = 0; valid_car[i].total_time == maxtime; i++) //print those cars of longest time
		printf("%s ", valid_car[i].plate);

	printf("%d%d:%d%d:%d%d", (maxtime - maxtime % 60 - ((maxtime - maxtime % 60) / 60) % 60 * 60) / 3600 / 10, (maxtime - maxtime % 60 - ((maxtime - maxtime % 60) / 60) % 60 * 60) / 3600 - (maxtime - maxtime % 60 - ((maxtime - maxtime % 60) / 60) % 60 * 60) / 3600 / 10 * 10, ((maxtime - maxtime % 60) / 60) % 60 / 10, ((maxtime - maxtime % 60) / 60) % 60 - ((maxtime - maxtime % 60) / 60) % 60 / 10 * 10, maxtime % 60 / 10, maxtime % 60 - maxtime % 60 / 10 * 10);
}  //print the time 

void Initialize_cars()  //to initialize the array
{
	int i;
	for (i = 0; i < n; i++)  //initialize all the element in to INFINITY
	{
		car[i].time_in = INFINITY;
		car[i].time_out = INFINITY;
		valid_car[i].time_in = INFINITY;
		valid_car[i].time_out = INFINITY;
		valid_car[i].total_time = 0;
	}

}
int timetransform(int hour, int min, int sec) //to transform the time into second
{
	return hour * 3600 + min * 60 + sec;
}

void Load_record() //to load the records
{
	int hour, min, sec;   
	int time;           //stored in secend 
	int flag = 0;      
	int i, j;     //loop variable
	int temp;     
	char plate_num[7];   //the plate number
	char car_status[3];  //the status
	for (i = 0; i < n; i++)  // read n records
	{
		scanf("%s", plate_num);        //read the plate number,time and status
		scanf("%d:%d:%d", &hour, &min, &sec);
		scanf("%s", car_status);
		time = timetransform(hour, min, sec); //store the time in second
		for (j = 0; j < i; j++)          //to find the previous record of this car
		{
			if (!strcmp(plate_num, car[j].plate)) //this car already had a record
			{
				if ((car[j].time_in != INFINITY) && (car[j].time_out != INFINITY)) //both the in-time and out-time are exist
				{
					if ((time<car[j].time_out) && (time>car[j].time_in))   
					{
						if (!strcmp(car_status, "in")) //the current in-time is later than the stored one
						{
							temp = car[j].time_in;      //renew the store
							car[j].time_in = time;
							time = temp;
							break;                 
						}
						else {                      // the current out- time is ealier than the stored one
							temp = car[j].time_out; //renew the store
							car[j].time_out = time;
							time = temp;
							break;
						}
					}

				}
				else if ((car[j].time_in == INFINITY) && (!strcmp(car_status, "in")))// the in-time of this record is empty
					                                                                 //and the current record is an in record 
				{
					if (time < car[j].time_out)   //if the in-time <the stored out-time                                     
					{
						car[j].time_in = time;  //store the record in this node
						flag = 1;
						break;
					}
					else
						continue;
				}
				else if ((car[j].time_out == INFINITY) && (!strcmp(car_status, "out")))// the out-time of this record is empty
				{                                                                       //and the current record is an out record 
					if (time > car[j].time_in)  //if the out-time > the stored in-time      
					{
						car[j].time_out = time; //store the record in this node
						flag = 1;
						break;
					}
					else	 continue;
				}
				else if ((car[j].time_out != INFINITY) && (!strcmp(car_status, "out"))) // the out-time of this record is  not empty
				{                                                                       //and the current record is an out record 
					if (car[j].time_out >time)   //the current out-time>the stored out-time
					{ 
						temp = car[j].time_out;   //swap their position to make sure that the smaller one can be visited firstly 
						car[j].time_out = time;   //when an in-record is read
						time = temp;
						continue;
					}
					else continue;
				}
				else if ((car[j].time_in != INFINITY) && (!strcmp(car_status, "in")))  //the same as above 
				{
					if (car[j].time_in <time)  //the current out-time>the stored out-time
					{
						temp = car[j].time_in;  //swap their position to make sure that the bigger one can be visited firstly 
						car[j].time_in = time;  //when an out-record is read
						time = temp;
						continue;
					}
					else continue;
				}
			}
		}
		if (flag == 0) {             //if this record has not been stored in an excited node

			strcpy(car[i].plate, plate_num);  //store the record in a new node
			if (!strcmp(car_status, "in"))
				car[i].time_in = time;
			else car[i].time_out = time;
		}
		else flag = 0;  
	}
}
void Valid_record()   //to sort out those valid records
{
	int i = 0;   //the loop variable
	int j = 0;

	while (i<n)  //visit all the n records that been read
	{
		if ((car[i].time_in != INFINITY) && (car[i].time_out != INFINITY))  //both in-time and out-time are existed
		{
			valid_car[j].time_in = car[i].time_in;    //load it into the valid_car array
			valid_car[j].time_out = car[i].time_out;
			strcpy(valid_car[j].plate, car[i].plate);
			valid_car[j].total_time = valid_car[j].time_out - valid_car[j].time_in;  //calculate the total time
			j++;  
		}
		i++;     //visit next record
	}
	number = j + 1;  //the number of the valid record

	 /*the following opration is to eliminate the case that one car is in two records at the same time*/
	for (i = 0; i<number; i++)   //for each record
	{
		for (j = i + 1; j<number; j++) 
		{
			if (!strcmp(valid_car[i].plate, valid_car[j].plate)) //firstly find the same car
			{
				if ((valid_car[i].time_in<valid_car[j].time_in) && (valid_car[i].time_out>valid_car[j].time_out))
				{                                       //if a car is in two records at the same time
					valid_car[i].time_in = INFINITY;   // we just fecth the one the has nearer in-time and out time
					valid_car[i].total_time = 0;
				}
				else if ((valid_car[i].time_in>valid_car[j].time_in) && (valid_car[i].time_out<valid_car[j].time_out))
				{
					valid_car[j].time_in = INFINITY;  
					valid_car[j].total_time = 0;
				}
			}
		}
	}
}
void Timeofcars()   //to calculate the total time of each car
{
	int i, j;
	int flag[MAX_SIZE] = { 0 };     //the flag indicating whether the record is visited
	for (i = 0; i < number; i++)    //for each valid record
	{
		if (flag[i] == 0) {     //if the record is not visited

			for (j = i + 1; j < number - 1; j++)   //to find the record of the same car
			{
				if (!strcmp(valid_car[i].plate, valid_car[j].plate))   //the record found
				{
					valid_car[i].total_time = valid_car[i].total_time + valid_car[j].total_time;  //add their time and store it
					flag[j] = 1;        //set this record as visited                              //in the previous node
				}
			}
		}
	}

}
int cmp(const void *a, const void *b) //the function to compare two structer

{
	Cars *c = (Cars*)a;
	Cars *d = (Cars*)b;
	 
	if (c->total_time != d->total_time)   //the main key-word is total time of each car
     	return d->total_time - c->total_time; //the bigger,the more ahead

	else
		return strcmp(c->plate, d->plate); //the plate number is the secendary key-word  
	                                        //in the order of alphabetical
}




