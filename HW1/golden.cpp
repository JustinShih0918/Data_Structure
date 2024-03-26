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

class Queue{
    public:
        Queue(int size);
        bool isEmpty();
        char Top();
        char Rear();
        void Push(char item);
        char Pop();
        void printQueue();
        bool isFull();
    private:
        int top;
        int rear;
        int capacity;
        char* queue;
        void doubleSize();
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
    Queue tools(1000);
    char movement[3];
    while (N--)
    {
        scanf("%s",movement);
        if(movement[0] == 'D'){
            int col;
            cin>>col;
            col++;
            char dig = miner.dig(col);
            if(dig == 'D'||dig == 'G') bag.Push(dig);
            else if(dig == 'B') miner.bomb(miner.getDig_row(),col);
            else if(dig == 'C') miner.lucky_clover(col,bag.Top());
            else if(dig == 'P') bag.pig();
            else tools.Push(dig);
            // miner.printMap();
            // tools.printQueue();
            // bag.printStack();
        }else if(movement[0] == 'U'){
            char use_tool = tools.Pop();
            if(use_tool == 'F') miner.flashlight();
            else if(use_tool == 'M'){
                for(int i = 1;i<=R;i++){
                    char dig = miner.dig(i);
                    if(dig == 'G' || dig == 'D') bag.Push(dig);
                    else if(dig == 'B') miner.bomb(miner.getDig_row(),i);
                    else if(dig == 'C') miner.lucky_clover(i,bag.Top());
                    else if(dig == 'P') bag.pig();
                    else tools.Push(dig);
                }
            }
            // miner.printMap();
            // tools.printQueue();
            // bag.printStack();
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
    memset(stack,'\0',sizeof(stack));
}
void Stack::doubleSize(){

    capacity *= 2;
    char *newStack = new char[capacity];
    memset(newStack,'\0',sizeof(newStack));
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

    if(top<capacity-1){
        stack[++top] = item;
    }
}

char Stack::Pop(){
    if(top>=0){
        return stack[top--];
    }
    else return '\0';
}

void Stack::pig(){
    while (!isEmpty()&& Top()!='D') Pop();
    // if(stack[top] == 'D') return;
    // int steal_from = -1;
    // for(int i = top;i>=0;i--){
    //     if(stack[i] == 'D'){
    //         steal_from = i+1;
    //         break;
    //     }
    //     else if(i == 0 && steal_from == -1) steal_from = 0;
    // }
    // for(int i = steal_from;i<=top;i++) stack[i] = '\0';
    // top = steal_from-1;
}

void Stack::printStack(){
    cout<<"FINAL BAG:"<<"\n";
    if(isEmpty()){
        cout<<"\n";
        return;
    }
    else{
        for(int i = top;i>=0;i--){
            cout<<stack[i]<<" ";
        }
        cout<<"\n";
    }
}

//Queue
Queue::Queue(int size){
    top = 0;
    rear = 0;
    capacity = size;
    queue = new char[size];
    memset(queue,'\0',sizeof(queue));
}

void Queue::doubleSize(){
    capacity*=2;
    char* newQueue = new char[capacity];
    memset(newQueue,'\0',sizeof(newQueue));
    int j = -1;
    for (int i = top; i <= rear; i++) {
        j++;
        newQueue[j] = queue[i];
    }
    top = 0;
    rear = j;
    delete [] queue;
    queue = newQueue;
}

bool Queue::isFull(){
    return (rear+1 == capacity);
}

bool Queue::isEmpty(){
    return (top == rear);
}

void Queue::printQueue(){
    cout<<"FINAL Tools:"<<"\n";
    if(isEmpty()) {
        cout<<"\n";
        return;
    }
    else{
        for(int i = top;i<rear;i++){
            cout<<queue[i]<<" ";
        }
        cout<<"\n";
    }
}

char Queue::Pop(){
    if(isEmpty()) return '\0';
    char answer = queue[top];
    for(int i = 0; i < rear-1; ++i) queue[i] = queue[i+1];
    rear--;
    return answer;
}

void Queue::Push(char item){
    if(isFull()) doubleSize();
    queue[rear++] = item;
}
char Queue::Top(){
    return queue[top];
}
char Queue::Rear(){
    return queue[rear];
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

int Map::getDig_row(){
    return Dig_row;
}

int Map::getRow(){
    return Row;
}

void Map::printMap(){
    cout<<"FINAL MAP:"<<"\n";
    int start_row = -1;
    for(int i = Row;i>=1;i--){
        for(int j = 1;j<=Col;j++){
            if(map[i][j]!='_'){
                start_row = i;
                break;
            }
        }
        if(start_row!=-1) break;
    }
    if(start_row == -1) return;
    else{
        for(int i = start_row;i>=1;i--){
            for(int j = 1;j<=Col;j++){
                cout<<map[i][j]<<" ";
            }
            cout<<"\n";
        }
    }
}

void Map::lucky_clover(int now_c,char input){
    if(input == '\0') return;
    int max = -1;
    for(int i = Row;i>=1;i--){
        for(int j = 1;j<=Col;j++){
            if(map[i][j]!='_'){
                max = i;
                break;
            }
        }
        if(max != -1) break;
    }
    max++;
    int count = 0;
    while (count<3)
    {
        for(int j = now_c-2;j<=Col&&j<=now_c+2;j++) map[max][j] = input;
        max++;
        count++;
    }
    if(max+2>Row) Row = max+2;
}

char Map::dig(int col){
    char answer;
    for(int i = Row;i>=1;i--){
        if(map[i][col]!='_'){
            answer = map[i][col];
            map[i][col] = '_';
            Dig_row = i;
            return answer;
        }
    }
    return '_';
}

void Map::flashlight(){
    int look_this_row = -1;
    for(int i = Row;i>=1;i--){
        for(int j = 1;j<=Col;j++){
            if(map[i][j]!='_'){
                look_this_row = i;
                break;
            }
        }
        if(look_this_row!=-1) break;
    }
    if(isEmpty()) {
        cout<<"MINE LEVEL:1\n_ _ _ _ _ _ \n";
        return;
    }
    else{
        cout<<"MINE LEVEL:"<<look_this_row<<"\n";
        for(int i = 1;i<=Col;i++){
            cout<<map[look_this_row][i]<<" ";
        }
        cout<<"\n";
    }
}

void Map::bomb(int now_r,int now_c){
    map[now_r][now_c] = '_';
    int r[8] = {0,1,1,1,0,-1,-1,-1};
    int c[8] = {-1,-1,0,1,1,1,0,-1};

    for(int i = 0;i<8;i++){
        int row = now_r+r[i];
        int col = now_c+c[i];
        map[row][col] = '_';
    }
}

bool Map::isEmpty(){
    for(int i = Row;i>=1;i--){
        for(int j = 1;j<=Col;j++){
            if(map[i][j]!='_') return false;
        }
    }
    return true;
}

