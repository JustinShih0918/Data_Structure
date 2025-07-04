#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <deque>
#include <string>

using namespace std;
const string Insert = "Insert";
const string Remove = "Remove";
const string Reorder = "Reorder";
const string Reverse = "Reverse";
const string Rotate = "Rotate";
const string Merge = "MergeListsPreserveOrder";

class Node{
public:
    int id;
    int level;
    Node(int i, int l) : id(i), level(l){}
    ~Node(){}
};

class List{
public:
    deque<Node> list;
    void insert(int i, int l){
        list.push_back(Node(i,l));
    }

    void remove(int idx){
        for(auto it = list.begin();it != list.end();it++){
            if(list.empty()) return;
            if((*it).id == idx){
                list.erase(it);
            }
        }
    }

    void rotate(int times){
        for(int i = 0;i<times;i++){
            auto target = prev(list.end());
            list.push_front(Node((*target).id,(*target).level));
            list.pop_back();
        }
    }

    void reorder(){
        vector<Node> odd;
        vector<Node> even;
        deque<Node> newList;

        for(int i = 0;i<list.size();i++){
            if(i%2 == 0) even.push_back(list[i]);
            else odd.push_back(list[i]);
        }

        for(int i = 0;i<even.size();i++){
            newList.push_back(even[i]);
        }
        for(int i = 0;i<odd.size();i++){
            newList.push_back(odd[i]);
        }

        list = newList;
    }

    void reverse(int l, int r){
        int len = r - l +1;
        for(int i = 0;i<len/2;i++){
            swap(list[l+i],list[r - i]);
        }
    }

    void print(int idx){
        cout << "List " << idx << "\n";
        if(list.empty()){
            cout << "Empty\n";
            return;
        }
        for(int i = 0;i<list.size();i++){
            cout << "ID: " << list[i].id << " Level: " << list[i].level << "\n";
        }
    }
};

bool cmp(Node a, Node b){
        if(a.level > b.level) return true;
        else if(a.level == b.level){
            if(a.id > b.id) return true;
            else return false;
        }
        else return false;
}

vector<List> mylist;

void printAns(){
    for(int i = 0;i<mylist.size();i++){
        mylist[i].print(i);
    }
}

int main(void){
    int n;
    cin >> n;
    for(int i = 0;i<n;i++) mylist.push_back(List());

    int amount;
    cin >> amount;
    while (amount--)
    {
        string command;
        cin >> command;
        if(command == Insert){
            int idx,id,level;
            cin >> idx >> id >>level;
            mylist[idx].insert(id,level);
        }
        else if(command == Remove){
            int idx,id;
            cin >> idx >> id;
            mylist[idx].remove(id);
        }
        else if(command == Rotate){
            int idx,times;
            cin >> idx >> times;
            mylist[idx].rotate(times);
        }
        else if(command == Reorder){
            int idx;
            cin >> idx;
            mylist[idx].reorder();
        }
        else if(command == Reverse){
            int idx,l,r;
            cin >> idx >> l >> r;
            mylist[idx].reverse(l,r);
        }
        else if(command == Merge){
            int idx1,idx2;
            cin >> idx1 >> idx2;
            deque<Node> &ListA = mylist[idx1].list;
            deque<Node> &ListB = mylist[idx2].list;
            ListA.clear();
            // deque<Node> newlist;
            // auto first = ListA.begin();
            // auto second = ListB.begin();

            // while (first != ListA.end() || second != ListB.end())
            // {
            //    if(first!=ListA.end() && second!=ListB.end()){
            //         if(cmp(*first,*second)) {
            //             newlist.push_back(*second);
            //             second++;
            //         }
            //         else{
            //             newlist.push_back(*first);
            //             first++;
            //         }
            //     }
            //     else if(first == ListA.end() && second!=ListB.end()){
            //         newlist.push_back(*second);
            //         second++;
            //     }
            //     else if(first != ListA.end() && second == ListB.end()){
            //         newlist.push_back(*first);
            //         first++;
            //     }
            //     else break;
            // }
            // mylist[idx2].list.clear();
            
        }
        //printAns();
    }
    printAns();
}