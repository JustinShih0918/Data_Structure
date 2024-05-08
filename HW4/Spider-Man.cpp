#include <bits/stdc++.h>
#include <iostream>
#include <cstdio>
using namespace std;

const string PLACE = "PLACE";
const string EDGE = "EDGE";
const string ORDER = "Order";
const string DROP = "Drop";
const string COMPLETE = "Complete";

class Delivery{
    public:
        int location;
        bool available;
        int order_ID;
        Delivery(int loc) : location(loc),available(true){}
};

class Order{
    public:
        int id;
        int ts;
        vector<Edge*> path;
        Order(int i,int t) : id(i),ts(t){}
};

class Edge{
    public:
        int p1;
        int p2;
        int dis;
        int capacity;
        Edge(int src,int des,int distance,int traffic) : p1(src),p2(des),dis(distance),capacity(traffic){};
};

class Vertex{
    public:
        int ID;
        int people;
        bool hasOrder;
        vector<pair<Vertex*,Edge*> > neighbors;
        Vertex(int id,int p) : ID(id), people(p), hasOrder(false){}
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
        void Dijkstra(int n,int v);
        // int Degree(int u); // return the degree of a vertex
        // void DeleteVertex(int v); // delete a vertex v
        // void DeleteEdge(int u, int v); // delete an edge (u, v)
    private:
        int n_v;
        int n_e;
        vector<Edge*> edge;
        vector<Vertex*> vertex;
        vector<Delivery> service;
        vector<Order> order;
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
    graph.PrintGraph(v);

    int num;
    cin>>num;
    while (num--)
    {
        cin>>com;
        if(com == ORDER){
            int id,src,ts;
            cin>>id>>src>>ts;
        }
        else if(com == DROP){
            int id,dst;
            cin>>id>>dst;
        }
        else if(com == COMPLETE){
            int id;
            cin>>id;
        }
    }
    
}

Graph::Graph(int v,int e):n_v(v),n_e(e){
    vertex.resize(105,NULL);
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
    service.push_back(Delivery(v));
}

