#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define INF 0x7fffffff
int FindSubMin(int *color,int i);
int main(){
    int N,M,L;
    int *EvaLike, *color;
    int i,j,k,count;
    scanf("%d",&N);
    scanf("%d",&M);
    EvaLike=(int*)malloc(sizeof(int)*M);
    for(i=0;i<M;i++){
        scanf("%d",&EvaLike[i]);
       if(EvaLike[i]>N)
            return 1;
        else continue;
    }
    scanf("%d",&L);
    color=(int*)malloc(sizeof(int)*L);
    for(i=0,count=0;count<L;count++){
        scanf("%d",&color[i]);
        for(j=0;j<M;j++){
            if(color[i]==EvaLike[j])
                break;
            else continue;
        }
        if(j<M){
            color[i]=j;
            i++;
        }
        else
            color[i]=INF;
    }
    int len = FindSubMin(color,i-1);
    printf("%d\n",len);
    return 0;
}
int FindSubMin(int *color,int i){
    int j,k;
    int *len=(int*)malloc(sizeof(int)*i);
    int maxlen=1;
    memset(len,0,sizeof(int)*i);
    for(j=0;j<=i;j++)
        len[j]=1;
    for(j=1;j<=i;j++){
        int max=0;
        for(k=0;k<j;k++){
            if(color[k]<=color[j]&&len[k]>max)
                max=len[k];
        }
        len[j]=max+1;
        if(maxlen<len[j])
            maxlen=len[j];
    }
    return maxlen;
}
