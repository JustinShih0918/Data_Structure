#include <iostream>
#include <vector>
using namespace std;

int N,K;


int main(void){
    cin>>N>>K;
    // int dp[1005] = {0};
    // int weight[105] = {0};
    // int value[105] = {0};
    vector<int> dp(K+1);
    vector<int> weight(N);
    vector<int> value(N);

    for(int i = 0;i<N;i++){
        cin>>value[i]>>weight[i];
    }

    for(int i = 0;i<N;i++){
        for(int j = K;j-weight[i]>=0;j--){
            dp[j] = max(dp[j],dp[j-weight[i]]+value[i]);
        }
    }
    cout<<dp[K]<<"\n";

}
