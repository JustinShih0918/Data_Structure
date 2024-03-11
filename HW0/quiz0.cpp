#include <iostream>
using namespace std;
int value[10];
int weight[10];
int N,K;
int less_weight = 2e9;

void getVal(int n,int now_val,int now_weight){
    if(n==N) return;

    if(now_val>=K && now_weight<less_weight){
        cout<<"do a change:"<<now_val<<" "<<K<<"\n";
        less_weight = now_weight;
    }
    
    getVal(n+1,now_val+value[n+1],now_weight+weight[n+1]);
    getVal(n+1,now_val,now_weight);
}

int main(void){
    cin>>N>>K;
    for(int i = 0;i<N;i++) cin>>value[i]>>weight[i];
    getVal(-1,0,0);
    cout<<less_weight<<"\n";
}