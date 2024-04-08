#include <string>
#include <iostream>
using namespace std;
const string a = "Attack";
const string n = "Neutral";
const string e = "Evolve";
const string com_Insert = "Insert";
const string com_Delete = "Delete";
const string com_Shuffle = "Shuffle";
const string com_Check = "Check";
const string com_Reverse = "Reverse";

class Node{
    friend class Chain;
    private:
        int poke;
        int damage;
        int health;
        int level;
        string stance;
    public:
        Node* next;
        Node* prev;
        Node(int type,int d,int h,string stage){
            poke = type;
            damage = d;
            health = h;
            stance = stage;
            level = 1;
            next = NULL;
            prev = NULL;
        }      
};

class Chain{
    public:
        Chain();
        void insert(int type,int d,int h,string stage);
        void deleteTarget();
        void deleteNode(Node* node_delete);
        void shuffle(char dire,int times);
        void check(int range);
        void reverse(int range);
        void emerge(Node *middle);
        void attack(Node* middle);
        void printChain();
        bool isEmpty();
    private:
        Node* head;
        Node* target;
        int num;
};

int main(void){
    Chain chain;
    int N;
    cin>>N;
    string command;
    while (N--)
    {
        cin>>command;
        if(command == com_Insert){
            int a,b,c;
            string state;
            cin>>a>>b>>c>>state;
            chain.insert(a,b,c,state);
        }
        else if(command == com_Delete) chain.deleteTarget();
        else if(command == com_Shuffle){
            char a;
            int b;
            cin>>a>>b;
            chain.shuffle(a,b);
        }
        else if(command == com_Check){
            int a;
            cin>>a;
            chain.check(a);
        }
        else if(command == com_Reverse){
            int a;
            cin>>a;
            chain.reverse(a);
        }
        //chain.printChain();
    }
    chain.printChain();
}

//chain
Chain::Chain(){
    target = NULL;
    head = NULL;
    num = 0;
}

void Chain::insert(int type,int d,int h,string stage){
    Node* newNode = new Node(type,d,h,stage);
    num++;
    if(target == NULL){
        head = newNode;
        target = head;
        target->next = target;
        target->prev = target;
    }
    else{
        newNode->next = target;
        newNode->prev = target->prev;
        target->prev->next = newNode;
        target->prev = newNode;
    }
    if(stage == e) emerge(newNode);
    else if(stage == a) attack(newNode);
    else return;
}

void Chain::emerge(Node *middle){
    if(middle->prev == middle->next && middle->prev == middle){
        middle->stance = n;
        return;
    }
    if(middle->prev != middle && middle->next != middle && middle->next != middle->prev && middle->poke == middle->prev->poke && middle->poke == middle->next->poke && middle->prev->level<3 && middle->next->level<3 && middle->level<3){
        middle->level = max(max(middle->prev->level,middle->next->level),middle->level)+1;
        middle->damage = max(max(middle->prev->damage,middle->next->damage),middle->damage);
        middle->health = max(max(middle->prev->health,middle->next->health),middle->health);
        target = middle;
        deleteNode(middle->prev);
        deleteNode(middle->next);
        middle->stance = n;
        return;
    }
    else{
        middle->stance = n;
        return;
    }
}
void Chain::attack(Node* middle){
    if(middle->prev == middle && middle->next == middle){
        middle->stance = n;
        return;
    }
    if(middle->prev == middle->next && middle != middle->prev){
        middle->prev->health -= middle->damage;
        if(middle->prev->health <= 0){
            if(middle->prev == target){
                target = middle;
                deleteNode(middle->prev);
            }
            else deleteNode(middle->prev);
        }
        middle->stance = n;
    }
    else{
        middle->prev->health -= middle->damage;
        middle->next->health -= middle->damage;
        if(middle->prev->health<=0){
            if(middle->prev == target){
                target = middle;
                deleteNode(middle->prev);
            }
            else deleteNode(middle->prev);
        }
        if(middle->next->health<=0){
            if(middle->next == target){
                target = middle;
                deleteNode(middle->next);
            }
            else deleteNode(middle->next);
        }
        middle->stance = n;
    }
}

void Chain::deleteNode(Node* node_delete){
    if(isEmpty()) return;
    Node* Next = node_delete->next;
    Next->prev = node_delete->prev;
    node_delete->prev->next = Next;
    num--;
    delete node_delete;
}

void Chain::deleteTarget(){
    if(isEmpty()) return;
    if(target->next == target && target->prev == target){
        delete target;
        target = NULL;
        head = NULL;
    }else{
        Node* Next = target->next;
        Next->prev = target->prev;
        target->prev->next = Next;
        delete target;
        target = Next;
    }
    num--;
}

void Chain::shuffle(char dire,int times){
    if(isEmpty()) return;
    Node* tmp = target;
    times = times%num;
    switch (dire)
    {
    case 'c':
        while (times--) tmp = tmp->next;
        break;
    case 'a':
        while (times--) tmp = tmp->prev;
        break;
    }
    int tmpVal = target->poke;
    target->poke = tmp->poke;
    tmp->poke = tmpVal;

    tmpVal = target->damage;
    target->damage = tmp->damage;
    tmp->damage = tmpVal;

    tmpVal = target->health;
    target->health = tmp->health;
    tmp->health = tmpVal;

    tmpVal = target->level;
    target->level = tmp->level;
    tmp->level = tmpVal;

    target = tmp;
}

void Chain::check(int range){
    Node* tail = target;
    Node* tmp = target;
    Node* pre;
    int arr[105] = {0};
    for(int i = 0;i<range;i++){
        arr[tail->poke] += 1;
        tail = tail->next;
    }

    for(int i = 0;i<range;i++){
        if(isEmpty()) break;
        if(arr[tmp->poke]>=2){
            pre = tmp->prev;
            if(tmp == target) deleteTarget();
            else deleteNode(tmp);
            tmp = pre;
        }
        tmp = tmp->next;
    }
}

void Chain::reverse(int range){
    Node* first = target;
    Node* tail = target;
    int cnt = 1;
    //target round
    if(range>num) range = num;

    while (first->next!=target)
    {
        cnt = 1;
        for(int i = 0;i<range-1;i++){
            tail = tail->next;
            if(tail == target){
                tail = tail->prev;
                break;
            }
            cnt++;
        }
        Node* new_first = tail->next;
        for(int i = 0;i<cnt/2;i++){
            int tmpVal = first->poke;
            first->poke = tail->poke;
            tail->poke = tmpVal;

            tmpVal = first->damage;
            first->damage = tail->damage;
            tail->damage = tmpVal;

            tmpVal = first->health;
            first->health = tail->health;
            tail->health = tmpVal;

            tmpVal = first->level;
            first->level = tail->level;
            tail->level = tmpVal;

            first = first->next;
            tail = tail->prev;
        }
        first = new_first;
        tail = first;
        if(first == target || first->next == target) break;
    }
    
    
}

void Chain::printChain(){
    if(isEmpty()) cout<<"no Poke Poke ;-;\n";
    else{
        cout<<"ID: "<<target->poke<<" HP: "<<target->health<<" LVL: "<<target->level<<"\n";
        Node* tmp = target->next;
        while (tmp!=target){
            cout<<"ID: "<<tmp->poke<<" HP: "<<tmp->health<<" LVL: "<<tmp->level<<"\n";
            tmp = tmp->next;
        }
    }
}

bool Chain::isEmpty(){
    if(target == NULL) return true;
    return false;
}
