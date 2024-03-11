#include <iostream>
#include <vector>
using namespace std;

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N,W;
    cin>>N>>W;
    vector<int> dp(W+1);
    vector<int> weight(N);
    vector<int> value(N);

    for(int i = 0;i<N;i++){
        for(int j = weight[i];j<=W;j++){
            dp[j] = max(dp[j],dp[j-weight[i]]+value[i]);
        }
    }

    cout<<dp[W]<<"\n";
}