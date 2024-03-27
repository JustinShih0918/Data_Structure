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
    Stack bag(10);
    Queue tools(10);
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
            else if (dig == 'M'||dig == 'F') tools.Push(dig);
            miner.updateRow();
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
                    else if (dig == 'M'||dig == 'F') tools.Push(dig);
                    miner.updateRow();
                }
                miner.updateRow();
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

    if(!isFull()){
        stack[++top] = item;
    }
}

char Stack::Pop(){
    if(isEmpty()) return '\0';
    char answer = stack[top];
    stack[top] = '\0';
    top--;
    return answer;
}

void Stack::pig(){
    while (!isEmpty()&& Top()!='D') Pop();
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
    memset(queue,'\0',sizeof(char)*capacity);
}

void Queue::doubleSize(){
    capacity*=2;
    char* newQueue = new char[capacity];
    memset(newQueue,'\0',sizeof(char)*capacity);
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
    queue[rear] = '\0';
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

void Map::updateRow(){
    bool hasChange = false;
    for(int i = Row;i>=0;i--){
        for(int j = 1;j<=Col;j++){
            if (map[i][j]!='_'){
                Row = i;
                hasChange = true;
                break;
            }
        }
        if(hasChange) break;
    }
}

int Map::getDig_row(){
    return Dig_row;
}

int Map::getRow(){
    return Row;
}

void Map::printMap(){
    cout<<"FINAL MAP:"<<"\n";
    if(isEmpty()) return;
    
    for(int i = Row;i>=1;i--){
        for(int j = 1;j<=Col;j++){
            cout<<map[i][j]<<" ";
        }
        cout<<"\n";
    }
    
}

void Map::lucky_clover(int now_c,char input){
    if(input == '\0' || isEmpty()) return;
    int L = max(1,now_c-2);
    int R = min(Col,now_c+2);
    int max = -1;
    for(int i = Row;i>=1;i--){
        for(int j = L;j<=R;j++){
            if(map[i][j]!='_'){
                max = i;
                break;
            }
        }
        if(max != -1) break;
    }
    int tmp = max;
    max++;
    int count = 0;
    while (count<3)
    {
        for(int j = L;j<=R;j++) map[max][j] = input;
        max++;
        count++;
    }
    if(tmp+3>Row) Row = tmp+3;
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
    Dig_row = -1;
    return '_';
}

void Map::flashlight(){
    if(isEmpty()) {
        cout<<"MINE LEVEL:1\n_ _ _ _ _ _ \n";
        return;
    }
    cout<<"MINE LEVEL:"<<Row<<"\n";
    for(int i = 1;i<=Col;i++){
        cout<<map[Row][i]<<" ";
    }
    cout<<"\n";
    
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

