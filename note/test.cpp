#include <bits/stdc++.h>
using namespace std;

int main(void){
    using QueuePair = pair<int,int>;
    priority_queue<QueuePair,vector<QueuePair>,greater<QueuePair> > pq;
    pq.push(QueuePair(3,1));
    pq.push(QueuePair(3,2));
    pq.push(QueuePair(3,3));
    pq.push(QueuePair(2,6));
    int len = pq.size();
    for(int i = 0 ;i<len;i++){
        QueuePair tmp = pq.top();
        pq.pop();
        cout<<tmp.first;
        cout<<tmp.second;
    }
}