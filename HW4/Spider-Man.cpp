#include <bits/stdc++.h>
#include <iostream>
#include <cstdio>
#include <queue>
#define ll long long
using namespace std;

const string PLACE = "PLACE";
const string EDGE = "EDGE";
const string ORDER = "Order";
const string DROP = "Drop";
const string COMPLETE = "Complete";

enum{
    waiting,delivery,finish
};

class Delivery{
    public:
        int location;
        bool available;
        int order_ID;
        int totalDis;
        Delivery(int loc) : location(loc),available(true),totalDis(0){}
};

class Edge{
    public:
        int p1;
        int p2;
        int dis;
        int capacity;
        Edge(int src,int des,int distance,int traffic) : p1(src),p2(des),dis(distance),capacity(traffic){};
};

class Order{
    public:
        int id;
        int ts;
        int src;
        int des;
        int status;
        vector<Edge*> path;
        Order(int i,int t,int s) : id(i),ts(t),src(s),status(waiting){}
};

class Vertex{
    public:
        int ID;
        int people;
        vector<pair<Vertex*,Edge*> > neighbors;
        vector<Delivery*> del;
        Vertex(int id,int p) : ID(id), people(p){
            if(p){
                for(int i = 0;i<p;i++){
                    del.push_back(new Delivery(id));
                }
            }
        }
        bool foundNeighbor(int target){
            for(auto it = neighbors.begin();it!=neighbors.end();it++){
                if((*it).first->ID == target) return true;
            }
            return false;
        }
        int findMan(int idx){
            for(int i = 0;i<people;i++){
                if(del[i]->order_ID == idx) return i;
            }
            return -1;
        }
        int Man_Dis(int idx){
            int man_idx = findMan(idx);
            return del[man_idx]->totalDis;
        }
        int available(){
            if(people<=0) return -1;
            for(int i = 0;i<people;i++){
                if(del[i]->available) return i;
            }
            return -1;
        }
};


class Graph{
    public:
        Graph(int v,int e);
        bool isEmpty();
        int NumberOfVertices() const{return n_v;}; // return the # of vertices
        int NumberOfEdges() const{return n_e;}; // return the # of edges
        int ExistsEdge(int u, int v); // check the existence of edge,if yes return index in Edge vector, if not return -1
        void InsertVertex(int v,int p); // insert a vertex v
        void InsertEdge(int u, int v,int dis,int tra); // insert an edge (u, v)
        void addDelivery(int v);
        void PrintGraph(int v);
        void dfs(int v);
        void printEdge(int v,Edge* e);
        void resetVisit();
        vector<int> Dijkstra(int src,int cap);
        void findDelivery(int src,int id,int cap);
        void DropDelivery(int id,int dst);
        void CompleteDelivery(int id);
        void updateStatus(int src,int des,int order_id,int mode,int distance,int man_idx);// 1 for order, 2 for drop, 3 for complete
        // int Degree(int u); // return the degree of a vertex
        // void DeleteVertex(int v); // delete a vertex v
        // void DeleteEdge(int u, int v); // delete an edge (u, v)
    private:
        int n_v;
        int n_e;
        vector<Edge*> edge;
        vector<Vertex*> vertex;
        vector<int> vertex_ID;
        vector<Delivery*> service;
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
        for(int j = 0;j<p;j++) graph.addDelivery(v);
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
            graph.findDelivery(src,id,ts);
        }
        else if(com == DROP){
            int id,dst;
            cin>>id>>dst;
            graph.DropDelivery(id,dst);
        }
        else if(com == COMPLETE){
            int id;
            cin>>id;
            graph.CompleteDelivery(id);
        }
    }
    
}

Graph::Graph(int v,int e):n_v(v),n_e(e){
    vertex.resize(105,NULL);
    order.resize(105,NULL);
    memset(visit,0,sizeof(visit));
}

bool Graph::isEmpty(){
    return n_v == 0;
}

int Graph::ExistsEdge(int u,int v){
    int len = edge.size();
    for(int i = 0;i<len;i++){
        if(edge[i]->p1 == u && edge[i]->p2 == v) return i;
    }
    return -1;
}

void Graph::InsertVertex(int v,int p){
    Vertex *vert = new Vertex(v,p);
    vertex[v] = vert;
    vertex_ID.push_back(v);
}

void Graph::InsertEdge(int u, int v,int dis,int tra){
    Edge *edg = new Edge(u,v,dis,tra);
    edge.push_back(edg);
    if(!vertex[u]) InsertVertex(u,0);
    if(!vertex[v]) InsertVertex(v,0);
    vertex[u]->neighbors.push_back(pair<Vertex*,Edge*>(vertex[v],edg));
    vertex[v]->neighbors.push_back(pair<Vertex*,Edge*>(vertex[u],edg));
}

void Graph::printEdge(int v,Edge* e){
    cout<<"Using edges with dis: "<<e->dis<<" cap: "<<e->capacity<<endl;
    if(e->p1 == v) cout<<"Going from "<<e->p1<<" to "<<e->p2;
    else cout<<"Going from "<<e->p2<<" to "<<e->p1;
    cout<<endl;
}

void Graph::resetVisit(){
    memset(visit,0,sizeof(visit));
}

void Graph::PrintGraph(int v){
    resetVisit();
    dfs(v);
}
void Graph::dfs(int v){
    cout<<vertex[v]->ID<<"\n";
    visit[v] = 1;

    for(auto i = vertex[v]->neighbors.begin();i!=vertex[v]->neighbors.end();i++){
        if(!visit[(*i).first->ID]){
            printEdge(v,(*i).second);
            dfs((*i).first->ID);
        }
    }   
}

void Graph::addDelivery(int v){
    service.push_back(new Delivery(v));
}

vector<int> Graph::Dijkstra(int src,int cap){
    int n = vertex[src]->neighbors.size();
    vector<int> d(105,INT_MAX);
    using QueuePair = pair<int,int>;
    priority_queue<QueuePair,vector<QueuePair>,greater<QueuePair> > pq;
    d[src] = 0;
    pq.push(QueuePair(d[src],src));
    while (pq.size())
    {
        auto [u_dis,u] = pq.top();
        pq.pop();
        //cout<<"pop u:"<<u<<"\n";
        if(d[u] < u_dis) continue;

        vector<QueuePair> adj;
        int len = vertex[u]->neighbors.size();
        //cout<<len<<"\n";
        for(int i = 0;i<len;i++){
            //cout<<"push :"<<vertex[u]->neighbors[i].second->dis<<" "<<vertex[u]->neighbors[i].first->ID<<"\n";
            adj.push_back(QueuePair(vertex[u]->neighbors[i].second->dis,vertex[u]->neighbors[i].first->ID));
        }
        for(auto [cost,v] : adj){
            if(cost + d[u]<d[v]){
                //cout<<"update v: "<<v<<"original: "<<d[v]<<endl;
                d[v] = d[u]+cost;
                pq.push(QueuePair(d[v],v));
                //cout<<"new: "<<d[v]<<endl;
            }
        }
    }
    return d;
}

void Graph::updateStatus(int src,int des,int order_id,int mode,int distance,int man_idx){

    if(mode == 1){ //for order
        cout<<"Order "<<order_id<<" from: "<<src<<"\n";
        vertex[src]->people--;
        vertex[des]->people++;
        Delivery *man = vertex[src]->del[man_idx];
        man->order_ID = order_id;
        man->totalDis+=distance;
        man->available = false;
        man->location = des;
        vertex[src]->del.pop_back();
        vertex[des]->del.push_back(man);

        order[order_id]->status = delivery;
        order[order_id]->src = des;
    }
    else if(mode == 2){
        cout<<man_idx<<endl;
        Delivery *man = vertex[src]->del[man_idx];
        man->totalDis+=distance;
        cout<<"Order "<<order_id<<" distance: "<<man->totalDis<<"\n";
        vertex[src]->people--;
        vertex[des]->people++;

        man->location = des;
        vertex[src]->del.pop_back();
        vertex[des]->del.push_back(man);

        order[order_id]->src = des;
    }
    else if(mode == 3){
        Delivery *man = vertex[src]->del[man_idx];
        man->available = true;
        man->totalDis = 0;
        order[order_id]->status = finish;
    }

    //cout<<src<<endl;
    //cout<<vertex[des]->del.back()->location<<endl;
}

void Graph::findDelivery(int src,int id,int cap){
    order[id] = new Order(id,cap,src);
    vector<int> list = Dijkstra(src,cap);
    int des;
    int dis = INT_MAX;
    bool found = false;
    int man_idx;
    for(auto it = vertex_ID.begin();it!=vertex_ID.end();it++){
        //cout<<"the vertex "<<(*it)<<" dis is "<<list[(*it)]<<"\n";
        if(vertex[(*it)]->available()>=0){
            if(list[(*it)]<dis){
                dis = list[(*it)];
                des = (*it);
                found = true;
                man_idx = vertex[(*it)]->available();
            }
            else if(list[(*it)] == dis && found){
                if(vertex[(*it)]->foundNeighbor(src) && vertex[des]->foundNeighbor(src)){
                    if(des > list[(*it)]){
                        dis = list[(*it)];
                        des = (*it);
                        man_idx = vertex[(*it)]->available();
                    }
                }
                else if(vertex[(*it)]->foundNeighbor(src) && !vertex[des]->foundNeighbor(src)){
                    dis = list[(*it)];
                    des = (*it);
                    man_idx = vertex[(*it)]->available();
                }
            }
        }
    }

    if(found){
        updateStatus(des,src,id,1,dis,man_idx);
        //cout<<"with distance: "<<dis<<endl;
    }
    else{
        cout<<"Just walk. T-T\n";
        order[id] = NULL;
    }
}

void Graph::DropDelivery(int id,int dst){
    int src = order[id]->src;
    vector<int> list = Dijkstra(dst,order[id]->ts);
    int dis = INT_MAX;
    bool found = false;

    if(list[src]!=INT_MAX){
        found = true;
        dis = list[src];
    }

    if(found){
        updateStatus(src,dst,id,2,dis,vertex[src]->findMan(id));
    }
    else{
        cout<<"No Way Home\n";
    }
}


void Graph::CompleteDelivery(int id){
    int distance = vertex[order[id]->src]->Man_Dis(id);
    cout<<order[id]->src<<" "<<vertex[order[id]->src]->findMan(id)<<endl;
    updateStatus(order[id]->src,0,id,3,0,vertex[order[id]->src]->findMan(id));
    Order *next;
    vector<Order*> or_list;
    bool found = false;
    for(int i = 0;i<105;i++){
        if(order[i]!=NULL && order[i]->status == waiting){
            found = true;
            next = order[i];
            or_list.push_back(next);
        }
    }

    if(found){
        int len = or_list.size();
        bool found_path = false;
        for(int i = 0;i<len;i++){
            int src = or_list[i]->src;
            vector<int> list = Dijkstra(src,or_list[i]->ts);
            int des;
            int dis = INT_MAX;
            int man_idx;
            for(auto it = vertex_ID.begin();it!=vertex_ID.end();it++){
                //cout<<"the vertex "<<(*it)<<" dis is "<<list[(*it)]<<"\n";
                man_idx = vertex[(*it)]->available();
                if(vertex[(*it)]->available()>=0){
                    if(list[(*it)]<dis){
                        dis = list[(*it)];
                        des = (*it);
                        found_path = true;
                        man_idx = vertex[(*it)]->available();
                    }
                    else if(list[(*it)] == dis && found){
                        if(vertex[(*it)]->foundNeighbor(src) && vertex[des]->foundNeighbor(src)){
                            if(des > list[(*it)]){
                                dis = list[(*it)];
                                des = (*it);
                                man_idx = vertex[(*it)]->available();
                            }
                        }
                        else if(vertex[(*it)]->foundNeighbor(src) && !vertex[des]->foundNeighbor(src)){
                            dis = list[(*it)];
                            des = (*it);
                            man_idx = vertex[(*it)]->available();
                        }
                    }
                }
            }
            if(found_path){
                cout<<"Order "<<id<<" distance: "<<distance<<"\n";
                updateStatus(src,des,id,1,dis,man_idx);
                order[id] = NULL;
                break;
            }
        }
    }
}
