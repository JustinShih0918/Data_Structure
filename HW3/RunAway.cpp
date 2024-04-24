#include <bits/stdc++.h>
#include <iostream>
using namespace std;
const string Add = "Add";
const string Delete = "Delete";
const string Check = "Check";
int result = 0;
int path_root = 0;
class Node{
    private:
        int val;
        int distance;
        int child_amount;
    public:
        int d1,d2;
        Node* parent;
        vector<Node*> child;
        Node(int v,int d){
            child_amount = 0;
            val = v;
            distance = d;
            d1 = 0;
            d2 = 0;
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
            amount = 0;
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
        void deleteVal(int val){
            for(int i = 0;i<amount;i++){
                if(node_index[i] == val){
                    node_index.erase(node_index.begin()+i,node_index.begin()+i+1);
                    break;
                }
            }
        }
        void deleteNode(int val){
            if(city[val] == NULL) return;
            deleteVal(val);
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
        void reset(){
            for(int i = 0;i<amount;i++){
                city[node_index[i]]->setD1(0);
                city[node_index[i]]->setD2(0);
            }
        }
        void solve(Node* current){
            if(current->getChildAmount() <=0 ){
                current->setD1(0);
                current->setD2(0);
                if(current->getDis()>result){
                    result = current->getDis();
                    path_root = current->getVal();
                }
                return;
            }

            for(int i = 0;i<current->getChildAmount();i++){
                solve(current->child[i]);
                if(current->child[i]->d1+current->child[i]->getDis() > current->d1){
                    current->setD2(current->d1);

                    int val = current->child[i]->d1+current->child[i]->getDis();
                    current->setD1(val);
                    // cout<<"choose d1: "<<current->child[i]->getVal()<<"\n";
                    // cout<<"the d1 change to: "<<current->d1<<"\n";

                }else if(current->child[i]->d1+current->child[i]->getDis() > current->d2){
                    int val = current->child[i]->d1+current->child[i]->getDis();
                    current->setD2(val);
                    // cout<<"choose d2: "<<current->child[i]->getVal()<<"\n";
                    // cout<<"the d2 change to: "<<current->d2<<"\n";
                }

                if(current->getDis()+current->d1+current->d2 > result){
                    result = current->getDis()+current->d1+current->d2;
                    path_root = current->getVal();
                }
            }
        }
        void check(int mode){
            solve(root);
            if(mode == 1){
                cout<<"Maximum Value: "<<result<<"\n";
                cout<<"Root of the Path: "<<path_root<<"\n";
            }
            else{
                cout<<"Final Root: "<<path_root<<"\n";
                return;
            }
            result = 0;
            path_root = root->getVal();
            reset();
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
            c.check(1);
        }
        //c.printCity();
    }
    c.check(2);
}

