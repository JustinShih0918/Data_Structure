#include <iostream>
#include <stdlib.h>
using namespace std;

int N,K;

int steal(int n,int totalweight,int totalval, int value[],int weight[]){
    int tmpVal;
    int tmpWeight;
    if(totalweight>=K || n==N-1) return totalval;
    else{
        tmpVal =totalval+value[n];
        tmpWeight = totalweight+weight[n];


    }
    
}


int main(void){
    cin>>N>>K;
    int* value = (int*)malloc(sizeof(int)*N);
    int* weight = (int*)malloc(sizeof(int)*N);

    for(int i = 0;i<N;i++){
        cin>>value[i]>>weight[i];
    }

    free(value);
    free(weight);
}
