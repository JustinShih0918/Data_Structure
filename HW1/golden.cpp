#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

class Stack{
    public:
        Stack(int size);
        bool isEmpty();
        char Top();
        void Push(char item);
        char Pop();
        void pig();
        void printStack();
        bool isFull();
    private:
        int top;
        int capacity;
        char* stack;
        void doubleSize();
};

class cQueue{
    public:
        cQueue(int size);
        bool isFull();
        bool isEmpty();
        void enQueue(char item);
        char deQueue();
        void printQueue();
        void doubleSize();
    private:
        int capacity;
        int front;
        int rear;
        char* cqueue;
};

class Map{
    public:
        Map(int r,int c);
        void printMap();
        void lucky_clover(int now_c,char input);
        char dig(int col);
        void flashlight();
        void bomb(int now_r,int now_c);
        int getDig_row();
        int getRow();
        bool isEmpty();
        void updateRow();
    private:
        char map[1005][1005];
        int Row;
        int Col;
        int Dig_row;
};

int main(void){
    int R,L,N;
    cin>>R>>L>>N;
    Map miner(L,R);
    Stack bag(1000);
    cQueue inventory(100);
    char movement[5];
    while (N--)
    {
        scanf("%s",movement);
        if(movement[0] == 'D'){
            int col;
            cin>>col;
            col++;
            char dig = miner.dig(col);
            miner.updateRow();
            if(dig == 'D'||dig == 'G') bag.Push(dig);
            else if(dig == 'B') miner.bomb(miner.getDig_row(),col);
            else if(dig == 'C') miner.lucky_clover(col,bag.Top());
            else if(dig == 'P') bag.pig();
            else if (dig == 'M'||dig == 'F') inventory.enQueue(dig);
            miner.updateRow();
            //miner.printMap();
            //bag.printStack();
        }else if(movement[0] == 'U'){
            char use_tool = inventory.deQueue();
            if(use_tool == 'F') miner.flashlight();
            else if(use_tool == 'M'){
                for(int i = 1;i<=R;i++){
                    char dig = miner.dig(i);
                    miner.updateRow();
                    if(dig == 'G' || dig == 'D') bag.Push(dig);
                    else if(dig == 'B') miner.bomb(miner.getDig_row(),i);
                    else if(dig == 'C') miner.lucky_clover(i,bag.Top());
                    else if(dig == 'P') bag.pig();
                    else if (dig == 'M'||dig == 'F') inventory.enQueue(dig);
                    miner.updateRow();
                }
                miner.updateRow();
            }
            //miner.printMap();
            //bag.printStack();
        }
    }
    bag.printStack();
    miner.printMap();
}

char Stack::Top(){
    return stack[top];
}

Stack::Stack(int size){
    capacity = size;
    top = -1;
    stack = new char[size];
    memset(stack,'\0',sizeof(char)*capacity);
}
void Stack::doubleSize(){

    capacity *= 2;
    char *newStack = new char[capacity];
    memset(newStack,'\0',sizeof(char)*capacity);
    for (int i = 0 ; i < capacity/2; i++) {
        newStack[i] = stack[i];
    }

    delete [] stack;   
    stack = newStack;
}

bool Stack::isFull(){
    return (top == capacity-1);
}

bool Stack::isEmpty(){
    if(top>=0) return false;
    else return true;
}

void Stack::Push(char item){
    if(isFull()) doubleSize();

    stack[++top] = item;

}

char Stack::Pop(){
    if(isEmpty()) return '\0';
    char answer = stack[top];
    stack[top] = '\0';
    top--;
    return answer;
}

void Stack::pig(){
    if(isEmpty()) return;
    while (!isEmpty() && Top()!='D') Pop();
}

void Stack::printStack(){
    cout<<"FINAL BAG:"<<"\n";
    if(isEmpty()){
        cout<<"\n";
        return;
    }
    else{
        for(int i = 0;i<=top;i++){
            cout<<stack[i]<<" ";
        }
        cout<<"\n";
    }
}

//Map 
Map::Map(int r,int c){
    memset(map,'_',sizeof(map));
    int n = 0;
    int amount = r*c;
    for(int i = r;i>=1 && n<=amount;i--){
        for(int j = 1;j<=c && n<=amount;j++){
            cin>>map[i][j];
            n++;
        }
    }
    Row = r;
    Col = c;
    Dig_row = -1;
}

void Map::updateRow(){
    bool hasChange = false;
    for(int i = Row;i>=1;i--){
        for(int j = 1;j<=Col;j++){
            if (map[i][j]!='_'){
                Row = i;
                hasChange = true;
                break;
            }
        }
        if(hasChange) break;
    }
    if(isEmpty()) Row = 1;
}

int Map::getDig_row(){
    return Dig_row;
}

int Map::getRow(){
    return Row;
}

void Map::printMap(){
    cout<<"FINAL MAP:\n";
    if(isEmpty()) return;
    
    for(int i = Row;i>=1;i--){
        for(int j = 1;j<=Col;j++){
            cout<<map[i][j]<<" ";
        }
        cout<<"\n";
    }
    
}

void Map::lucky_clover(int now_c,char input){
    if(isEmpty()) return;
    map[Dig_row][now_c] = '_';
    if(input == '\0') return;
    int L = max(1,now_c-2);
    int R = min(Col,now_c+2);
    
    int tmp = Row;
    int max = Row;
    max++;
    int count = 0;
    while (count<3)
    {
        for(int j = L;j<=R;j++) map[max][j] = input;
        max++;
        count++;
    }
    if(tmp+3>Row) Row = tmp+3;
    updateRow();
}

char Map::dig(int col){
    char answer = '_';
    if(isEmpty()){
        Dig_row = -1;
        return answer;
    }
    for(int i = Row;i>=1;i--){
        if(map[i][col]!='_'){
            answer = map[i][col];
            if(map[i][col]!='C') map[i][col] = '_';
            Dig_row = i;
            return answer;
        }
    }
    return answer;
}

void Map::flashlight(){
    if(isEmpty()) Row = 1;

    updateRow();
    cout<<"MINE LEVEL:"<<Row<<"\n";
    for(int i = 1;i<=Col;i++){
        cout<<map[Row][i]<<" ";
    }
    cout<<"\n";
}

void Map::bomb(int now_r,int now_c){
    int r[8] = {0,1,1,1,0,-1,-1,-1};
    int c[8] = {-1,-1,0,1,1,1,0,-1};

    for(int i = 0;i<8;i++){
        int row = now_r+r[i];
        int col = now_c+c[i];
        map[row][col] = '_';
    }
    updateRow();
}

bool Map::isEmpty(){
    for(int i = Row;i>=1;i--){
        for(int j = 1;j<=Col;j++){
            if(map[i][j]!='_') return false;
        }
    }
    return true;
}

// cQueue
cQueue::cQueue(int size){
    capacity = size;
    front = -1;
    rear = -1;
    cqueue = new char[capacity];
    memset(cqueue,'\0',sizeof(char)*capacity);
}

void cQueue::doubleSize(){
    int size = capacity*2;
    char* newCqueue = new char[size];

    int start = (front+1)*capacity;
    if(start<2){
        copy(cqueue+start,cqueue+capacity,newCqueue);
        copy(cqueue,cqueue+rear+1,newCqueue+capacity-start);
    }

    front = 2*capacity-1;
    rear = capacity-2;
    capacity *= 2;
    delete [] cqueue;
    cqueue = newCqueue;
}

bool cQueue::isEmpty(){
    if(front == -1) return true;
    else return false;
}
bool cQueue::isFull(){
    if(front == 0 && rear == capacity-1) return true;
    if(front == rear+1) return true;
    return false;
}
void cQueue::enQueue(char item){
    if(isFull()) doubleSize();
    else{
        if(front == -1) front = 0;
        rear = (rear+1)%capacity;
        cqueue[rear] = item;
        //cout<<"add "<<item<<"\n";
    }
}
char cQueue::deQueue(){
    char item;
    if(isEmpty()) return '\0';
    else{
        item = cqueue[front];
        cqueue[front] = '\0';
        if(front == rear){
            front = -1;
            rear = -1;
        }
        else{
            front = (front+1)%capacity;
        }
        //cout<<"delete "<<item<<"\n";
        return item;
    }
}



