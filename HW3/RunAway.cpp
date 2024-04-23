#include <bits/stdc++.h>
#include <iostream>
using namespace std;
const string Add = "Add";
const string Delete = "Delete";
const string Check = "Check";

class Node{
    private:
        int val;
        int distance;
        int child_amount;
    public:
        Node* parent;
        vector<Node*> child;
        Node(int v,int d){
            child_amount = 0;
            val = v;
            distance = d;
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
            cout<<"My parent:\n";
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
        int amount;
    public:
        City(int index,int dis){
            Node *node = new Node(index,dis);
            node->parent = NULL;
            city.push_back(node);
            amount = 1;
        }
        void addNode(int par,int val,int dis){
            bool exist = false;
            Node* node;
            for(int i = 0;i<amount;i++){
                if(city[i]->getVal() == val){
                    city[i]->setDis(dis);
                    exist = true;
                    node = city[i];
                    break;
                }
            }
            if(!exist) node = new Node(val,dis);
            
            bool found = false;
            for(int i = 0;i<amount;i++){
                if(city[i]->getVal() == par){
                    node->parent = city[i];
                    city[i]->addChild(node);
                    found = true;
                    break;
                }
            }
            if(!found){
                Node* parent_node = new Node(par,0);
                node->parent = parent_node;
                parent_node->addChild(node);
                city.push_back(parent_node);
                amount++;
            }

            if(!exist){
                city.push_back(node);
                amount++;
            }   
        }
        void deleteNode(int val){
            for(int i = 0;i<amount;i++){
                if(city[i]->getVal() == val){
                    city[i]->setParent(city[i]->parent);
                    city[i]->parent->deleteChild(city[i]);
                    city.erase(city.begin()+i,city.begin()+i+1);
                    amount--;
                    return;
                }
            }
            return;
        }
        void printCity(){
            for(int i = 0;i<amount;i++){
                city[i]->printNode();
            }
        }
        void check(){
            return;
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
        c.printCity();
    }
    
}

