#include <bits/stdc++.h>
#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;
using PathInfo = pair<vector<int>,vector<int> >; //first d, second path
using FinalPath = pair<pair<int,int>,vector<int> >;//first dst and distance,second path
const string PLACE = "PLACE";
const string EDGE = "EDGE";
const string ORDER = "Order";
const string DROP = "Drop";
const string COMPLETE = "Complete";

enum{
    WAITING,DELIVERY,FINISH
};

class Edge{
    public:
        int p1;
        int p2;
        int dis;
        int capacity;
        Edge(int src,int des,int distance,int traffic) : p1(src),p2(des),dis(distance),capacity(traffic){};
};
using adjacent = pair<int,Edge*>;

class Order{
    public:
        int id;
        int ts;
        int src;
        int restaurant;
        int dst;
        int status;
        int Dtotal;
        vector<int> path_src_res;
        vector<int> path_res_dst;
        Order(int i,int t,int s) : id(i),ts(t),src(s),dst(-1),status(WAITING),Dtotal(0){}
};
using adjacent = pair<int,Edge*>;
class Vertex{
    public:
        int ID;
        int people;
        vector<adjacent > neighbors;
        Vertex(int id,int p) : ID(id), people(p){}
        bool foundNeighbor(int target){
            for(auto it = neighbors.begin();it!=neighbors.end();it++){
                if((*it).first == target) return true;
            }
            return false;
        }
};

class Graph{
    public:
        Graph(int v,int e);
        int NumberOfVertices() const{return n_v;}; // return the # of vertices
        int NumberOfEdges() const{return n_e;}; // return the # of edges
        void InsertVertex(int v,int p); // insert a vertex v
        void InsertEdge(int u, int v,int dis,int tra); // insert an edge (u, v)
        void PrintGraph(int v);
        void dfs(int v);
        void printEdge(int v,Edge* e);
        void resetVisit(){memset(visit,0,sizeof(visit));}
        PathInfo Dijkstra(int src,int cap);
        FinalPath ChoosePath_take(int src,int cap);
        FinalPath ChoosePath_Drop(int src,int cap,int dst);
        void TakeOrder(int src,int id,int cap);
        void DropOrder(int id,int dst);
        void CompleteOrder(int id);
        Order* ChooseOrder();
        void PathRecover(int id);
    private:
        int n_v;
        int n_e;
        Edge *edge[105][105];
        vector<Vertex*> vertex;
        vector<int> vertex_ID;
        vector<int> order_ID;
        vector<Order*> order;
        int visit[105];
};


int main(void){
    int V,E,D;
    cin>>V>>E>>D;
    Graph graph(V,E);
    string com;
    int v,p;
    for(int i = 0;i<D;i++){
        cin>>com;
        cin>>v>>p;
        graph.InsertVertex(v,p);
    }
    for(int i = 0;i<E;i++){
        cin>>com;
        int src,des,dis,tra;
        cin>>src>>des>>dis>>tra;
        graph.InsertEdge(src,des,dis,tra);
    }
    //graph.PrintGraph(v);
    int num;
    cin>>num;
    while (num--)
    {
        cin>>com;
        if(com == ORDER){
            int id,src,ts;
            cin>>id>>src>>ts;
            graph.TakeOrder(src,id,ts);
        }
        else if(com == DROP){
            int id,dst;
            cin>>id>>dst;
            graph.DropOrder(id,dst);
        }
        else if(com == COMPLETE){
            int id;
            cin>>id;
            graph.CompleteOrder(id);
        }
    } 
}

Graph::Graph(int v,int e) : n_v(v), n_e(e){
    vertex.resize(105,NULL);
    order.resize(105,NULL);
    memset(visit,0,sizeof(visit));
    memset(edge,NULL,sizeof(edge));
}

void Graph::InsertVertex(int v,int p){
    Vertex *ver = new Vertex(v,p);
    vertex[v] = ver;
    vertex_ID.push_back(v);
}

void Graph::InsertEdge(int u, int v,int dis,int tra){
    Edge *edg = new Edge(u,v,dis,tra);
    edge[u][v] = edg;
    edge[v][u] = edg;
    if(!vertex[u]) InsertVertex(u,0);
    if(!vertex[v]) InsertVertex(v,0);

    vertex[u]->neighbors.push_back(adjacent(v,edg));
    vertex[v]->neighbors.push_back(adjacent(u,edg));
}

void Graph::printEdge(int v,Edge* e){
    cout<<"Using edges with dis: "<<e->dis<<" cap: "<<e->capacity<<endl;
    if(e->p1 == v) cout<<"Going from "<<e->p1<<" to "<<e->p2;
    else cout<<"Going from "<<e->p2<<" to "<<e->p1;
    cout<<endl;
}

void Graph::dfs(int v){
    cout<<vertex[v]->ID<<"\n";
    visit[v] = 1;

    for(auto i = vertex[v]->neighbors.begin();i!=vertex[v]->neighbors.end();i++){
        if(!visit[(*i).first]){
            printEdge(v,(*i).second);
            dfs((*i).first);
        }
    }   
}

void Graph::PrintGraph(int v){
    resetVisit();
    dfs(v);
}

PathInfo Graph::Dijkstra(int src,int cap){
    vector<int> d(105,INT_MAX);
    using QueuePair = pair<int,int>;
    priority_queue<QueuePair,vector<QueuePair>,greater<QueuePair> > pq;
    d[src] = 0;
    pq.push(QueuePair(d[src],src));
    vector<int> path(105,-1);
    while (pq.size())
    {
        auto [u_dis,u] = pq.top();
        pq.pop();
        if(d[u] < u_dis) continue;

        vector<QueuePair> adj;
        int len = vertex[u]->neighbors.size();
        for(int i = 0;i<len;i++){
            adj.push_back(QueuePair(vertex[u]->neighbors[i].second->dis,vertex[u]->neighbors[i].first));
        }
        for(auto [cost,v] : adj){
            if(cost + d[u]<d[v]){
                d[v] = d[u]+cost;
                pq.push(QueuePair(d[v],v));
                path[v] = u;
            }
        }
    }
    return PathInfo(d,path);
}

FinalPath Graph::ChoosePath_take(int src,int cap){
    PathInfo info = Dijkstra(src,cap);
    int dst;
    int distance = INT_MAX;
    bool found = false;
    for(auto it = vertex_ID.begin();it!=vertex_ID.end();it++){
        int index = (*it);
        if(vertex[index]->people>0){
            if(info.first[index]<distance){
                distance = info.first[index];
                dst = index;
                found = true;
            }
            else if(info.first[index] == distance && found){
                if(vertex[index]->foundNeighbor(src) && vertex[dst]->foundNeighbor(src)){
                    if(index<dst){
                        dst = index;
                    }
                }
                else if(vertex[index]->foundNeighbor(src) && !vertex[dst]->foundNeighbor(src)){
                    dst = index;
                }
            }
        }
    }

    if(found) return FinalPath(pair<int,int>(dst,distance),info.second);
    else return FinalPath(pair<int,int>(-1,0),info.second);

}

void Graph::TakeOrder(int src,int id,int cap){
    Order *fresh = new Order(id,cap,src);
    order_ID.push_back(id);
    FinalPath fp = ChoosePath_take(src,cap);

    if(fp.first.first!=-1){
        vertex[fp.first.first]->people--;
        fresh->src = fp.first.first;
        fresh->restaurant = src;
        fresh->status = DELIVERY;
        fresh->Dtotal+=fp.first.second;
        vector<int> path;
        int tmp = fp.first.first;
        while (tmp!=-1)
        {
            path.push_back(fp.second[tmp]);
            tmp = fp.second[tmp];
        }
        fresh->path_src_res = path;
        order[id] = fresh;
        cout<<"ID "<<id<<" from: "<<fresh->src<<"\n";
    }
    else cout<<"Just walk. T-T\n";
}

FinalPath Graph::ChoosePath_Drop(int src,int cap,int dst){
    PathInfo info = Dijkstra(src,cap);
    int distance;
    cout<<info.first[dst]<<endl;
    if(info.first[dst]!=INT_MAX){
        distance = info.first[dst];
        return FinalPath(pair<int,int>(dst,distance),info.second);
    }
    else return FinalPath(pair<int,int>(-1,0),info.second);
}

void Graph::DropOrder(int id,int dst){
    Order *target = order[id];
    cout<<target->ts<<endl;
    FinalPath fp = ChoosePath_Drop(dst,target->ts,target->restaurant);
    
    if(fp.first.first!=-1){
        target->dst = dst;
        target->Dtotal+=fp.first.second;
        vector<int> path;
        int tmp = fp.first.first;
        while (tmp != -1)
        {
            path.push_back(fp.second[tmp]);
            tmp = fp.second[tmp];
        }
        target->path_res_dst = path;
        cout<<"Order "<<id<<" distance: "<<target->Dtotal<<"\n";
    }
    else{
        target->dst = dst;
        cout<<"No Way Home\n";
    }
}

Order* Graph::ChooseOrder(){
    for(int i = 0;i<105;i++){
        if(order[i] && order[i]->dst!=-1 && order[i]->status == DELIVERY) return order[i];
    }
    return NULL;
}

void Graph::CompleteOrder(int id){
    Order *target = order[id];
    target->status = FINISH;
    int DIS = target->Dtotal;
    vertex[target->dst]->people++;

    Order *next = ChooseOrder();
    if(next){
        DropOrder(next->id,next->dst);
    }
}

void Graph::PathRecover(int id){
    
}





