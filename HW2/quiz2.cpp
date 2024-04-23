#include <bits/stdc++.h>
#include <iostream>
using namespace std;
int n;
const string Insert = "Insert";
const string Remove = "Remove";
const string Rotate = "Rotate";
const string Reorder = "Reorder";
const string Reverse = "Reverse";
const string Merge = "MergeListsPreserveOrder";

class Node{
    public:
        Node* next;
        Node(int a,int b){
            level = b;
            ID = a;
            next = NULL;
        }
        int getLevel(){
            return level;
        }
        int getID(){
            return ID;
        }
        void setID(int id){
            ID = id;
        }
        void setLevel(int lev){
            level = lev;
        }
    private:
        int level;
        int ID;
};

class List{
    public:
        Node*list[100]; 
        Node*tail[100];
        List(int k){
            n = k;
            for(int i = 0;i<k;i++){
                list[i] = new Node(0,0);
                tail[i] = list[i];
                num[i] = 0;
            }
        }
        void insert(int index,int id,int level){
            if(list[index]->getID() == 0 && num[index] == 0){
                list[index]->setID(id);
                list[index]->setLevel(level);
                num[index]++;
            }
            else{
                tail[index]->next = new Node(id,level);
                tail[index] = tail[index]->next;
                num[index]++;
            }
        }
        void remove(int index,int id){
            Node* pre = list[index];
            Node* target = list[index];
            if(isEmpty(index)) return;
            for(int i = 0;target != NULL;i++){
                if(target->getID() == id){
                    Node *newTarget = target->next;
                    deleteNode(target,pre,index);
                    target = newTarget;
                }
                else{
                    pre = target;
                    target = target->next;
                }
            }
        }
        void deleteNode(Node* target,Node* pre,int index){
            if(target == list[index] && target->next == NULL){
                list[index]->setID(0);
                list[index]->setLevel(0);
                tail[index] = list[index];
            }
            else if(target == list[index] && target->next !=NULL){
                list[index] = target->next;
            }
            else pre->next = target->next;
            //delete target;
            num[index]--;
        }
        void rotate(int index,int times){
            while (times--)
            {
                Node* tmp = list[index];
                Node* pre;
                while (tmp!=NULL)
                {
                    pre = tmp;
                    tmp = tmp->next;
                }
                Node* newhead = tmp;
                newhead->next = list[index];
                list[index] = newhead;
                pre->next = NULL;
            }
        }
        bool isEmpty(int index){
            if(list[index]->getID() == 0) return true;
            else return false;
        }
        void reorder(int index);
        void reverse(int index,int l,int r){
            Node* R = list[index];
            Node* L = list[index];
            for(int i = 1;i<r;i++) R = R->next;
            for(int i = 1;i<l;i++) L = L->next;
            int amount = r-l+1;
            for(int i = 0;i<amount/2;i++){
                int tmp = L->getID();
                L->setID(R->getID());
                R->setID(tmp);

                tmp = L->getLevel();
                L->setLevel(R->getLevel());
                R->setLevel(tmp);

                L = L->next;
            }
        }
        void merge();
        void printList(){
            for(int i = 0;i<n;i++){
                cout<<"List "<<i<<"\n";
                Node* tre = list[i];
                if(isEmpty(i)){
                        cout<<"Empty\n";
                }
                else {
                    for(int j = 0;j<num[i];j++){
                        cout<<"ID: "<<tre->getID()<<" Level: "<<tre->getLevel()<<"\n";
                        tre = tre->next;
                    }
                }
            }
        }
    private:
        int n;
        int num[1000];
};


int main(void){
    cin>>n;
    List l(n);
    string command;
    int com;
    cin>>com;
    while (com--)
    {
        cin>>command;
        if(command == Insert){
            int a,b,c;
            cin>>a>>b>>c;
            l.insert(a,b,c);
        }
        else if(command == Remove){
            int a,b;
            cin>>a>>b;
            l.remove(a,b);
        }
        else if(command == Rotate){
            int a,b;
            cin>>a>>b;
            l.rotate(a,b);
        }
        else if(command == Reorder){
            int a;
            cin>>a;
        }
        else if(command == Reverse){
            int a,b,c;
            cin>>a>>b>>c;
        }
        else if(command == Merge){
            int a,b;
            cin>>a>>b;
        }
        l.printList();
    }
    l.printList();
}