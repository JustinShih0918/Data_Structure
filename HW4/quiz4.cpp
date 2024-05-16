#include <bits/stdc++.h>
#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;

class Edge{
    public:
        int from;
        int to;
        int w;
        Edge(int u,int v,int weight) : from(u), to(v), w(weight){}
};

class Node{
    public:
        int Serial;
        vector<Edge*> adjList;
        Node(int s) : Serial(s){}
};
int totalDis;
int ans;
int test;
int test_ans;
bool found_A;
bool found_B;
void reset(){
    test = 0;
    test_ans = 0;
    totalDis = 0;
    ans = 0;
    found_A = false;
    found_B = false;
}
class Graph{
    public:
        vector<Node> nodeList;
        vector<Edge*> edgeList;
        Graph(int n){
            for(int i = 0;i<n;i++) nodeList.push_back(Node(i));
        }
        void print(){
            for(int i = 0;i<edgeList.size();i++) cout<<"from "<< edgeList[i]->from<<" to "<<edgeList[i]->to<<" w "<<edgeList[i]->w<<endl;
            for(int i = 0;i<nodeList.size();i++){
                cout<<"I am "<<nodeList[i].Serial<<endl;
                cout<<"having: \n";
                for(int j = 0;j<nodeList[i].adjList.size();j++){
                    cout<<nodeList[i].adjList[j]->to;
                }
                cout<<"\n";
            }
        }
        void addEdge(int from,int to,int w){
            Edge* edg = new Edge(from,to,w);
            edgeList.push_back(edg);
            nodeList[from].adjList.push_back(edg);
        }
        void findMinPath(int from,int to,int mode){
            int len = nodeList[from].adjList.size();
            for(int i = 0;i<len;i++){
                Edge* edge = nodeList[from].adjList[i];
                //cout<<"visit from "<<from<<" to "<< edge->to<<"\n";
                //cout<<"now ans:"<<ans<<endl;
                if(edge->to == to){
                    totalDis+=edge->w;
                    //cout<<"now dis:"<<totalDis<<endl;
                    if(found_A){
                        if(totalDis < ans) ans = totalDis;
                    }
                    else{
                        ans = totalDis;
                        found_A = true;
                    }
                    totalDis -= edge->w;
                    return;
                }
                else{
                    totalDis += edge->w;
                    //cout<<"at else: "<<totalDis<<endl;
                    findMinPath(edge->to,to,mode);
                    totalDis -= edge->w;
                }
            }
            return;
        }
};

int main(void){
    int n,m,t;
    cin >> n >> m;
    Graph graph(n);
    for(int i = 0;i<m;i++){
        int from,to,w;
        cin >> from >> to >> w;
        graph.addEdge(from,to,w);
    }
    //graph.print();
    cin >> t;
    if(t == 1){
        int A,dest;
        cin >> A >> dest;
        reset();
        graph.findMinPath(A,dest,1);
        if(!found_A) cout<<-1<<"\n";
        else cout<<ans<<"\n";
    }
    else if( t == 2){
        int A,B,dest;
        cin >> A >> B >> dest;
        reset();
        graph.findMinPath(A,B,1);
        graph.findMinPath(B,dest,2);
        if(found_A && found_B) cout<<totalDis<<"\n";
        else cout<<-1<<"\n";
    }
}