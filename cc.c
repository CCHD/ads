#include<stdio.h>
#include<stdlib.h>
#define INF_MAX 0x7fffffff
#define Not_Arrive 0
#define Arrive 1
typedef struct station Stop;
struct station{
	float price;
	int distance;
	int state;
	float rest_gas;
};
int cmp(const void* a,const void* b){
	Stop *aa=(Stop*)a;
	Stop *bb=(Stop*)b;
	return (aa->distance-bb->distance);
}
int main(){
	int tank,distance,gas_dis,N,gas_price;
	scanf("%d",&tank);
	scanf("%d",&distance);
	scanf("%d",&gas_dis);
	scanf("%d",&N);

	int i;
	Stop *s;
	s=(Stop*)malloc(sizeof(Stop)*(N+1));
	for(i=0;i<N;i++){
		scanf("%f%d",&s[i].price,&s[i].distance);
		s[i].state=Not_Arrive;
		s[i].rest_gas=0;
	}
	s[N].distance=distance;
	s[N].price=INF_MAX;
	s[N].state=Arrive;
	s[N].rest_gas=0;
	qsort(s,N,sizeof(Stop),cmp);

	float money = 0;
	if(s[0].distance!=0){
		printf("The maximum travel distance = 0.00\n");
		return 0;
	}
	i=0;
	int j,k,tmp;
	int len=gas_dis*tank;
	while(s[i].state==Not_Arrive){
		k=i+1;
		if(i!=0)
		s[i].rest_gas=s[tmp].rest_gas-((float)(s[i].distance-s[tmp].distance))/gas_dis;
		for(;k<N&&s[k].price>=s[i].price&&(s[i].distance+len>=s[k].distance);k++){
			
		}
		if((s[i].distance+len)<s[k].distance){
			k=k-1;
		}
		if(s[k].price<s[i].price&&(s[i].distance+len>=s[k].distance)){
			float tmp_use=((float)(s[k].distance-s[i].distance))/gas_dis;
			if(tmp_use>s[i].rest_gas){
				money=money+s[i].price*(tmp_use-s[i].rest_gas);
				s[i].rest_gas=tmp_use;
			}
		}
		else if(s[i].distance+len>=s[k].distance&&s[i].price<=s[k].price){
			if(i==N-1){
				if(s[i].distance+s[i].rest_gas*gas_dis>=s[N].distance);
				else{
					float tmp_use=((float)(s[N].distance-s[i].distance))/gas_dis;
					money=money+s[i].price*(tmp_use-s[i].rest_gas);
				}
			}
			else{
				money=money+s[i].price*(tank-s[i].rest_gas);
				s[i].rest_gas=tank;
			}
		}
		else{
			float length=s[i].distance+len;
			printf("The maximum travel distance = %.2f\n",length);
			return 0;
		}
		tmp=i;
		i=k;
	}
	printf("%.2f\n",money);
}

