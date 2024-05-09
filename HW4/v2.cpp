#include <bits/stdc++.h>
#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;
using PathInfo = pair<pair<int,int>,vector<int> >; //first dst and distance, second path
using QueuePair = pair<int,int>;//first d[u], second u
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
        Edge* findEdge(int v){
            for(auto it = neighbors.begin();it!=neighbors.end();it++){
                if((*it).first == v) return (*it).second;
            }
        }
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
        PathInfo Dijkstra(int src,int cap,int des, int mode);
        void TakeOrder(int src,int id,int cap);
        void DropOrder(int id,int dst,bool drop);
        void CompleteOrder(int id);
        Order* ChooseOrder();
        void PathRecover(int id,int mode);
        void PathCutting(int id,int mode);
        void PrintAllEdge();
    private:
        int n_v;
        int n_e;
        Edge *edge[105][105];
        vector<pair<int,int> > edge_ID;
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
    //graph.PrintAllEdge();
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
            graph.DropOrder(id,dst,true);
        }
        else if(com == COMPLETE){
            int id;
            cin>>id;
            graph.CompleteOrder(id);
        }
        //graph.PrintAllEdge();
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
    edge_ID.push_back(pair<int,int>(u,v));
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

void Graph::PrintAllEdge(){
    int len = edge_ID.size();
    for(int i = 0;i<len;i++){
        Edge* target = edge[edge_ID[i].first][edge_ID[i].second];
        cout<<"u: "<<target->p1<<" v: "<<target->p2<<" distance: "<<target->dis<<" cap: "<<target->capacity<<"\n";
    }
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

PathInfo Graph::Dijkstra(int src,int cap,int des,int mode){
    vector<int> d(105,INT_MAX);
    
    priority_queue<QueuePair,vector<QueuePair>,greater<QueuePair> > pq;
    d[src] = 0;
    pq.push(QueuePair(d[src],src));
    vector<int> path(105,-1);
    int dst = -1;
    bool found = false;
    if(vertex[src]->people>0){
        dst = src;
        found = true;
    }
    while (pq.size())
    {
        auto [u_dis,u] = pq.top();
        pq.pop();
        if(d[u] < u_dis) continue;
        vector<QueuePair> adj;
        int len = vertex[u]->neighbors.size();
        for(int j = 0;j<105;j++){
            for(int i = 0;i<len;i++){
                if(vertex[u]->neighbors[i].first == j) adj.push_back(QueuePair(vertex[u]->neighbors[i].second->dis,vertex[u]->neighbors[i].first));
            }
        }
        for(auto [cost,v] : adj){
            Edge *edg = vertex[u]->findEdge(v);
            if(cost + d[u]<d[v] && edg->capacity>=cap){
                d[v] = d[u]+cost;
                pq.push(QueuePair(d[v],v));
                path[v] = u;
                if(vertex[v]->people>0){
                    if(!found){
                        dst = v;
                        found = true;
                    }
                    if(d[v] < d[dst] && found){
                        dst = v;
                    }
                }
            }
        }
    }
    if(mode ==1){
        if(found){
            return PathInfo(QueuePair(d[dst],dst),path);
        }
        else return PathInfo(QueuePair(-1,-1),path);
    }
    else if(mode == 2){
        return PathInfo(QueuePair(d[des],des),path);
    }
}

void Graph::TakeOrder(int src,int id,int cap){
    Order *fresh = new Order(id,cap,src);
    order_ID.push_back(id);
    PathInfo fp = Dijkstra(src,cap,0,1); // first: distance, dst / second: path

    if(fp.first.second!=-1){
        vertex[fp.first.second]->people--;
        fresh->src = fp.first.second;
        fresh->restaurant = src;
        fresh->status = DELIVERY;
        fresh->Dtotal+=fp.first.first;
        vector<int> path;
        int tmp = fp.first.second;
        while (tmp!=-1)
        {
            path.push_back(tmp);
            tmp = fp.second[tmp];
        }
        fresh->path_src_res = path;
        // for(int i = 0;i<fresh->path_src_res.size();i++) cout<<fresh->path_src_res[i];
        // cout<<endl;
        order[id] = fresh;
        PathCutting(id,1);
        cout<<"Order "<<id<<" from: "<<fresh->src<<"\n";
    }
    else cout<<"Just walk. T-T\n";
}

void Graph::DropOrder(int id,int dst, bool drop){
    Order *target = order[id];
    PathRecover(id,1);
    PathInfo p = Dijkstra(dst,target->ts,target->restaurant,2);
    if(p.first.first!=INT_MAX){
        target->dst = dst;
        target->Dtotal+=p.first.first;
        vector<int> path;
        int tmp = p.first.second;
        while (tmp != -1)
        {
            path.push_back(tmp);
            tmp = p.second[tmp];
        }
        target->path_res_dst = path;
        // for(int i = 0;i<target->path_res_dst.size();i++) cout<<target->path_res_dst[i];
        // cout<<endl;
        PathCutting(id,2);
        cout<<"Order "<<id<<" distance: "<<target->Dtotal<<"\n";
    }
    else if(drop){
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
    PathRecover(id,2);
    target->status = FINISH;
    vertex[target->dst]->people++;
    // for(int i = 0;i<vertex_ID.size();i++){
    //     cout<<"ID: "<<vertex_ID[i]<<" people: "<<vertex[vertex_ID[i]]->people<<endl;
    // }
    Order *next = ChooseOrder();
    if(next){
        DropOrder(next->id,next->dst, false);
    }
}

void Graph::PathCutting(int id,int mode){
    Order *ord = order[id];
    int traffic = ord->ts;
    if(mode == 1){
        int len = ord->path_src_res.size();
        for(int i = 0;i<len-1;i++){
            int u,v;
            u = ord->path_src_res[i];
            v = ord->path_src_res[i+1];
            edge[u][v]->capacity-=traffic;
        }
    }
    else{
        int len = ord->path_res_dst.size();
        for(int i = 0;i<len-1;i++){
            int u,v;
            u = ord->path_res_dst[i];
            v = ord->path_res_dst[i+1];
            edge[u][v]->capacity-=traffic;
        }
    }
}

void Graph::PathRecover(int id, int mode){
    Order *ord = order[id];
    int traffic = ord->ts;
    if(mode == 1){
        int len = ord->path_src_res.size();
        for(int i = 0;i<len-1;i++){
            int u,v;
            u = ord->path_src_res[i];
            v = ord->path_src_res[i+1];
            edge[u][v]->capacity+=traffic;
        }
    }
    else{
        int len = ord->path_res_dst.size();
        for(int i = 0;i<len-1;i++){
            int u,v;
            u = ord->path_res_dst[i];
            v = ord->path_res_dst[i+1];
            edge[u][v]->capacity+=traffic;
        }
    }
}