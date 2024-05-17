#include <bits/stdc++.h>
#include <iostream>
#include <vector>
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
    WAITING,DELIVERY,INLINE,FINISH
};

class Edge{
    public:
        int p1;
        int p2;
        int distance;
        int capacity;
        Edge(int u,int v,int dis,int traffic) : p1(u), p2(v), distance(dis), capacity(traffic){}
};
using Adjacent = pair<int,Edge*>;

class Order{
    public:
        int id;
        int ts;
        int delivery_man;
        int restaurant;
        int destination;
        int status;
        int distance_total;
        vector<int> path_man_to_res;
        vector<int> path_res_to_des;
        Order(int i,int t,int r) : id(i), ts(t), delivery_man(-1), restaurant(r),
                                   destination(-1), status(WAITING), distance_total(0){}
};

class Vertex{
    public:
        int ID;
        int man;
        vector<Adjacent> neighbors;
        Vertex(int id,int p): ID(id), man(p){}
        void printNeighbor(){
            int len = neighbors.size();
            cout<<ID<<" has:\n";
            for(int i = 0;i<len;i++){
                cout<<neighbors[i].first<<" ";
            }
            cout<<endl;
        }
        Edge* findEdge(int v){
            for(auto it = neighbors.begin();it != neighbors.end();it++){
                if((*it).first == v) return (*it).second; 
            }
        }
};

class Graph{
    private:
        int n_v;
        int n_e;
        Edge *edge[105][105];
        vector<pair<int,int>> edge_ID;
        vector<Vertex*> vertexList;
        vector<int> vertexID;
        vector<int> orderID;
        vector<Order*> order;
    public:
        Graph(int v,int e) : n_v(v), n_e(e){
            vertexList.resize(105,NULL);
            order.resize(105,NULL);
            memset(edge,NULL,sizeof(edge));
        }
        void InsertVertex(int v,int p);
        void InsetEdge(int u,int v,int dis,int tra);
        PathInfo Dijkstra_Set(int src,int des,int cap);
        PathInfo findMinPath(int src,int des,int cap);
        void SetOrder(int id,int res,int cap);
        void DropOrder(int id,int des,bool drop);
        void CompleteOrder(int id);
        Order* ChooseOrder();
        void Recover(int id,int mode);
        void Cutting(int id,int mode);
        void SortNeighbor();
};


int main(void){
    int V,E,D;
    cin >> V >> E >> D;
    Graph graph(V,E);
    string com;
    for(int i = 0;i<D;i++){
        cin>>com;
        int v,p;
        cin >> v >> p;
        graph.InsertVertex(v,p);
    }
    for(int i = 0;i<E;i++){
        cin>>com;
        int u,v,dis,tra;
        cin >> u >> v >> dis >> tra;
        graph.InsetEdge(u,v,dis,tra);
    }
    graph.SortNeighbor();
    int num;
    cin >> num;
    while (num--)
    {
        cin >> com;
        if(com == ORDER){
            int id,res,ts;
            cin >> id >> res >> ts;
            graph.SetOrder(id,res,ts);
        }
        else if(com == DROP){
            int id,des;
            cin >> id >> des;
            graph.DropOrder(id,des,true);
        }
        else if(com == COMPLETE){
            int id;
            cin >> id;
            graph.CompleteOrder(id);
        }   
    }
}

void Graph::InsertVertex(int v,int p){
    Vertex* ver = new Vertex(v,p);
    vertexID.push_back(v);
    vertexList[v] = ver;
}
void Graph::InsetEdge(int u,int v,int dis,int tra){
    Edge* edg = new Edge(u,v,dis,tra);
    edge[u][v] = edg;
    edge[v][u] = edg;
    edge_ID.push_back(pair<int,int>(u,v));
    if(!vertexList[u]) InsertVertex(u,0);
    if(!vertexList[v]) InsertVertex(v,0);

    vertexList[u]->neighbors.push_back(Adjacent(v,edg));
    vertexList[v]->neighbors.push_back(Adjacent(u,edg));
}

bool compare(Adjacent a,Adjacent b){
    return a.first < b.first;
}

void Graph::SortNeighbor(){
    int len = vertexID.size();
    for(int i = 0;i<len;i++){
        sort(vertexList[vertexID[i]]->neighbors.begin(),vertexList[vertexID[i]]->neighbors.end(),compare);
    }
}
//QueuePair: first d[u], second u
//PathInfo: first distance and des, second path
// mode 1 for finding delivery man
PathInfo Graph::Dijkstra_Set(int src,int des,int cap){
    vector<int> d(105,2e9);
    priority_queue<QueuePair, vector<QueuePair>, greater<QueuePair> > pq;
    vector<int> path(105,-1);
    d[src] = 0;
    pq.push(QueuePair(d[src],src));
    int delivery = -1;
    bool foundDelivery = false;
    if(vertexList[src]->man > 0){
        delivery = src;
        foundDelivery = true;
    }
    while (pq.size())
    {
        auto [u_dis,u] = pq.top();
        pq.pop();
        if(d[u] < u_dis) continue;
        vector<QueuePair> adjacent;
        int len = vertexList[u]->neighbors.size();
        for(int i = 0;i<len;i++) {
            adjacent.push_back(QueuePair(vertexList[u]->neighbors[i].second->distance,vertexList[u]->neighbors[i].first));
        }
        for(auto [cost,v] : adjacent){
            Edge *edg = vertexList[u]->findEdge(v);
            if(cost + d[u] < d[v] && edg->capacity >= cap){
                d[v] = d[u] + cost;
                pq.push(QueuePair(d[v],v));
                path[v] = u;
                if(vertexList[v]->man > 0){
                    if(!foundDelivery){
                        delivery = v;
                        foundDelivery = true;
                    }
                    if(foundDelivery && d[v] < d[delivery]){
                        delivery = v;
                    }
                }
            }
        }
    }
    if(foundDelivery) return PathInfo(QueuePair(d[delivery],delivery),path);
    else return PathInfo(QueuePair(-1,-1),path);
}


PathInfo Graph::findMinPath(int src,int des,int cap){
    vector<int> d(105,2e9);
    priority_queue<QueuePair, vector<QueuePair>, greater<QueuePair> > pq;
    vector<int> path(105,-1);
    d[src] = 0;
    pq.push(QueuePair(d[src],src));
    while (pq.size())
    {
        priority_queue<QueuePair, vector<QueuePair>, greater<QueuePair> > p_test;
        p_test = pq;
        int len_1 = p_test.size();
        for(int i = 0 ;i<len_1;i++){
            QueuePair tmp = p_test.top();
            p_test.pop();
            cout<<tmp.first<<" "<<tmp.second;
            cout<<"\n";
        }
        auto [u_dis,u] = pq.top();
        cout<<"u is "<<u<<endl;
        pq.pop();
        if(d[u] < u_dis) continue;
        vector<QueuePair> adjacent;
        int len = vertexList[u]->neighbors.size();
        for(int i = 0;i<len;i++){
            adjacent.push_back(QueuePair(vertexList[u]->neighbors[i].second->distance,vertexList[u]->neighbors[i].first));
        }
        for(auto [cost, v] : adjacent){
            Edge* edg = vertexList[u]->findEdge(v);
            if(cost + d[u] < d[v] && edg->capacity >= cap){
                d[v] = d[u] + cost;
                pq.push(QueuePair(d[v],v));
                path[v] = u;
            }
        }
    }
    return PathInfo(QueuePair(d[des],des),path);
}



void Graph::SetOrder(int id,int res,int cap){
    Order *ord = new Order(id,cap,res);
    PathInfo pf = Dijkstra_Set(res,-1,cap);

    if(pf.first.first != -1){
        vertexList[pf.first.second]->man--;
        ord->delivery_man = pf.first.second;
        ord->status = DELIVERY;
        ord->distance_total += pf.first.first;
        vector<int> path;
        int tmp = pf.first.second;
        while (tmp != -1)
        {
            path.push_back(tmp);
            tmp = pf.second[tmp];
        }
        ord->path_man_to_res = path;
        order[id] = ord;
        orderID.push_back(id);
        Cutting(id,1);
        cout << "Order " << id << " from: "<< ord->delivery_man <<"\n";
    }
    else cout << "Just walk. T-T\n";
}
void Graph::DropOrder(int id,int des,bool drop){
    Order *target = order[id];
    if(target != NULL){
        if(drop) Recover(id,1);
        PathInfo pf = findMinPath(target->restaurant,des,target->ts);
        if(pf.first.first != 2e9){
            if(!drop) target->status = DELIVERY;
            target->destination = des;
            target->distance_total+=pf.first.first;
            vector<int> path;
            int tmp = pf.first.second;
            while (tmp != -1)
            {
                path.push_back(tmp);
                tmp = pf.second[tmp];
            }
            reverse(path.begin(),path.end());
            target->path_res_to_des = path;
            Cutting(id,2);
            cout<<"Order "<<id<<" distance: "<<target->distance_total<<"\n";
        }
        else{
            if(drop){
                target->destination = des;
                target->status = INLINE;
                cout<<"No Way Home\n";
            }
        }
    }
}
void Graph::CompleteOrder(int id){
    Order *target = order[id];
    if(target != NULL){
        Recover(id,2);
        target->status = FINISH;
        vertexList[target->destination]->man++;
        //cout<<"finish operation\n";
        Order *next = ChooseOrder();
        if(next) DropOrder(next->id,next->destination,false);
    }
}
Order* Graph::ChooseOrder(){
    //return NULL;
    int len = orderID.size();
    sort(orderID.begin(),orderID.end());
    for(int i = 0;i<len;i++){
        if(order[orderID[i]] != NULL && order[orderID[i]]->status == INLINE) return order[orderID[i]];
    }
    return NULL;
}
void Graph::Recover(int id,int mode){ // 1 for delivery to restaurant, 2 for restaurant to destination
    Order *ord = order[id];
    int t = ord->ts;
    if(mode == 1){
        int len = ord->path_man_to_res.size();
        for(int i = 0;i<len-1;i++){
            int u,v;
            u = ord->path_man_to_res[i];
            v = ord->path_man_to_res[i+1];
            edge[u][v]->capacity+=t;
        }
    }
    else if(mode == 2){
        int len = ord->path_res_to_des.size();
        for(int i = 0;i<len-1;i++){
            int u,v;
            u = ord->path_res_to_des[i];
            v = ord->path_res_to_des[i+1];
            edge[u][v]->capacity+=t;
        }
    }
}
void Graph::Cutting(int id,int mode){
    Order *ord = order[id];
    int traffic = ord->ts;
    if(mode == 1){
        int len = ord->path_man_to_res.size();
        for(int i = 0;i<len-1;i++){
            int u,v;
            u = ord->path_man_to_res[i];
            v = ord->path_man_to_res[i+1];
            edge[u][v]->capacity-=traffic;
        }
    }
    else{
        int len = ord->path_res_to_des.size();
        for(int i = 0;i<len-1;i++){
            int u,v;
            u = ord->path_res_to_des[i];
            v = ord->path_res_to_des[i+1];
            edge[u][v]->capacity-=traffic;
        }
    }
}
