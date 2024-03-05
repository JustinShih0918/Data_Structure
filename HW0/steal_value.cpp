#include <iostream>
#include <vector>
using namespace std;

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N,K;
    cin>>N>>K;
    vector<int> dp(K+1);
    vector<int> weight(N);
    vector<int> value(N);

    for(int i = 0;i<N;i++){
        cin>>value[i]>>weight[i];
        for(int j = K;j-weight[i]>=0;j--){
            dp[j] = max(dp[j],dp[j-weight[i]]+value[i]);
        }
    }
    cout<<dp[K]<<"\n";

}
