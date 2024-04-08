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
        chain.printChain();
    }
    chain.printChain();
}

//chain
Chain::Chain(){
    target = NULL;
    head = NULL;
}

void Chain::insert(int type,int d,int h,string stage){
    Node* newNode = new Node(type,d,h,stage);
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
        deleteNode(middle->prev);
        deleteNode(middle->next);
        middle->stance = n;
        target = middle;
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
        middle->prev->health-=middle->damage;
        if(middle->prev->health<=0){
            if(middle->prev == target) target = middle;
            deleteNode(middle->prev);
        }
        middle->stance = n;
    }
    else{
        middle->prev->health-=middle->damage;
        middle->next->health-=middle->damage;
        if(middle->prev->health<=0){
            if(middle->prev == target) target = middle;
            deleteNode(middle->prev);
        }
        if(middle->next->health<=0){
            if(middle->next == target) target = middle;
            deleteNode(middle->next);
        }
        middle->stance = n;
    }
}

void Chain::deleteNode(Node* node_delete){
    Node* Next = node_delete->next;
    Next->prev = node_delete->prev;
    node_delete->prev->next = Next;
    delete node_delete;
}

void Chain::deleteTarget(){
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
}

void Chain::shuffle(char dire,int times){
    Node* tmp = target;
    switch (dire)
    {
    case 'c':
        while (times--) tmp = tmp->next;
        break;
    case 'a':
        while (times--) tmp = tmp->prev;
        break;
    }

    Node* prevT = target->prev;
    Node* nextT = target->next;
    Node* prevTmp = tmp->prev;
    Node* nextTmp = tmp->next;

    prevT->next = tmp;
    nextT->prev = tmp;
    prevTmp->next = target;
    nextTmp->prev = target;

    target->prev = tmp->prev;
    target->next = tmp->next;
    tmp->prev = prevT;
    tmp->next = nextT;
}

void Chain::check(int range){
    //exist 2n method cause n<=100
    Node* tail = target;
    Node* tmp = target;
    Node* pre;
    int arr[105] = {0};
    for(int i = 0;i<range;i++){
        arr[tail->poke] += 1;
        tail = tail->next;
    }

    for(int i = 0;i<range;i++){
        for(int j = 1;j<=100;j++){
            if(j == tmp->poke && arr[j]>=2){
                pre = tmp->prev;
                if(tmp == target) deleteTarget();
                else deleteNode(tmp);
                tmp = pre;
                break;
            }
        }
        tmp  = tmp->next;
    }
    
}

void Chain::reverse(int range){
    Node *tmp = target;
    Node *tail = tmp;
    Node *tmp2;
    for(int i = 0;i<range-1 && tmp->next!=target;i++) tmp = tmp->next;

    while (tail!=tmp->next)
    {
        tmp2 = tail->prev;
        tail->prev = tail->next;
        tail->next = tmp2;
        tail = tail->prev;
    }
    // cout<<"6's prev is "<<tmp->prev->prev->poke<<endl;
    // cout<<"6's next is "<<tmp->prev->prev->poke<<endl;
    // cout<<"tmp is "<<tmp->poke<<"\n";
    // cout<<"tmp prev is "<<tmp->prev->poke<<endl;
    // cout<<"tmp next is "<<tmp->next->poke<<endl;
    // cout<<"tail is "<<tail->poke<<"\n";
    // cout<<"tail prev is "<<tail->prev->poke<<endl;
    // cout<<"tail next is "<<tail->next->poke<<endl;
    tail->next->next = tmp;
    target = tmp;
    
    //printChain();
    //next state
    Node *first = tail->next;
    tail = first;
    while (first->next!=target && first!=target)
    {
        for(int i = 0;i<range && tmp->next!=target;i++) first = first->next;
        while (tail!=first->next)
        {
            tmp2 = tail->prev;
            tail->prev = tail->next;
            tail->next = tmp2;
            tail = tail->prev;
        }
        tail->next->next = tmp;
    }
}

void Chain::printChain(){
    if(target == NULL) cout<<"no Poke Poke ;-;\n";
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
