
```c++
#include <bits/stdc++.h>
using namespace std;
#define long long ll
vector<ll> dijkstra(const vector<vector<pair<int, int>>> &G, int S)
{
    int n = G.size();
    vector<ll> d(n, INF);
    using QueuePair = pair<ll, int>;
    priority_queue<QueuePair, vector<QueuePair>, greater<QueuePair>> pq;
    d[S] = 0;
    pq.emplace(d[S], S);
    while(pq.size())
    {
        auto [u_dis, u] = pq.top();
        pq.pop();
        if(d[u] < u_dis) // 同一個點會被push進pq很多次，cost比較大在pq中會比較後面
            continue;
        for(auto [cost, v] : G[u])
        {
            if(cost + d[u] < d[v])
            {
                d[v] = d[u] + cost;
                pq.emplace(d[v], v);
            }
        }
    }
    return d;
}
```