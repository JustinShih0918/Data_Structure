#include <bits/stdc++.h>
#include <iostream>
using namespace std;
const string Add = "Add";
const string Delete = "Delete";
const string Check = "Check";
int result = 0;
class Node{
    private:
        int val;
        int a;
        int distance;
        int child_amount;
        int max;
    public:
        int d1,d2;
        Node* parent;
        vector<Node*> child;
        Node(int v,int d){
            child_amount = 0;
            val = v;
            a = val;
            distance = d;
            d1 = 0;
            d2 = 0;
            max = 0;
        }
        int getA(){
            return a;
        }
        int setA(int x){
            a = x;
        }
        int getVal(){
            return val;
        }
        int getDis(){
            return distance;
        }
        void setDis(int a){
            distance = a;
        }
        int getChildAmount(){
            return child_amount;
        }
        void setD1(int a){
            d1 = a;
        }
        void setD2(int a){
            d2 = a;
        }
        void setMax(){
            max = val+d1+d2;
        }
        void addChild(Node* node){
            child_amount++;
            child.push_back(node);
        }
        void deleteChild(Node* node){
            for(int i = 0;i<child_amount;i++){
                if(child[i]->val == node->val){
                    child.erase(child.begin()+i,child.begin()+i+1);
                    child_amount--;
                }
            }
        }
        void setParent(Node* par){
            for(int i = 0;i<child_amount;i++){
                child[i]->parent = par;
                par->child.push_back(child[i]);
                par->child_amount++;
            }
        }
        void printNode(){
            cout<<"I am "<<val<<" with distance : "<<distance<<"\n";
            cout<<"My parent: ";
            if(parent == NULL) cout<<"I am root\n";
            else cout<<parent->val<<"\n";
            cout<<"My child:\n";
            for(int i = 0;i<child_amount;i++){
                cout<<child[i]->val<<" ";
            }
            cout<<"\n";
        }
};

class City{
    private:
        vector<Node*> city;
        vector<int> node_index;
        int amount;
        Node* root;
    public:
        City(int index,int dis){
            city.resize(10050,NULL);
            node_index.push_back(index);
            Node *node = new Node(index,dis);
            node->parent = NULL;
            city[index] = node;
            amount++;
            root = node;
        }
        void addNode(int par,int val,int dis){
            Node* node;
            if(city[val]!=NULL){
                node = city[val];
                node->setDis(dis);
            }
            else{
                node = new Node(val,dis);
                city[val] = node;
                amount++;
                node_index.push_back(val);
            }

            if(city[par]!=NULL){
                city[par]->addChild(node);
                node->parent = city[par];
            }
            else{
                city[par] = new Node(par,0);
                city[par]->addChild(node);
                node->parent = city[par];
                amount++;
                node_index.push_back(par);
            }
        }
        void deleteNode(int val){
            if(city[val] == NULL) return;
            city[val]->setParent(city[val]->parent);
            city[val]->parent->deleteChild(city[val]);
            Node* tmp = city[val];
            delete tmp;
            city[val] = NULL;
            amount--;
        }
        void printCity(){
            for(int i = 0;i<10050;i++){
                if(city[i]) city[i]->printNode();
            }
        }
        void solve(Node* current,Node* prev){
            for(int i = 0;i<current->getChildAmount();i++){
                if(current == prev) continue;
                solve(current->child[i],current);
                if(current->child[i]->getA() > current->d1){
                    current->setD2(current->d1);
                    current->setD1(current->child[i]->getA());
                }
                else{
                    current->setD2(max(current->d2,current->child[i]->getA()));
                }
            }
            result = max(result,current->getA()+current->d1+current->d2);
            current->setA(current->getA()+current->d1);
        }
        void check(){
            solve(root,NULL);
            cout<<result;
        }
};

int main(void){
    int n,m;
    cin>>n>>m;
    int root_val,root_dis;
    cin>>root_val>>root_dis;
    City c(root_val,root_dis);
    for(int i = 0;i<n;i++){
        int par,val,dis;
        cin>>par>>val>>dis;       
        c.addNode(par,val,dis);
    }
    string command;
    while (m--)
    {
        cin>>command;
        if(command == Add){
            int par,val,dis;
            cin>>par>>val>>dis;
            c.addNode(par,val,dis);
        }
        else if(command == Delete){
            int val;
            cin>>val;
            c.deleteNode(val);
        }
        else if(command == Check){
            c.check();
        }
        //c.printCity();
    }
    
}

