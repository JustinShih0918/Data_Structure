#include <iostream>
using namespace std;

class Stack{
    public:
        Stack(int size);
        bool isEmpty();
        char Top();
        void Push(char item);
        char Pop();
        void view();
    private:
        int top;
        int capacity;
        char* stack;
};

class Map{
    public:
        Map(int r,int c);
        void printMap(int r,int c);
        void lucky_clover(int now_r,int now_c,char input);
        char dig(int col);
        void flashlight();
        bool isEmpty(); // not sure if i need this
    private:
        char map[1005][1005];
        int Row;
        int Col;
};

char Stack::Top(){
    return stack[top];
}

Stack::Stack(int size){
    stack = new char[size];
    capacity = size;
    top = -1;
}

bool Stack::isEmpty(){
    if(top>=0) return true;
    else return false;
}

void Stack::Push(char item){
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

Map::Map(int r,int c){
    int n = 0;
    int amount = r*c;
    memset(map,'\0',sizeof(map));
    for(int i = 1000;i>=1 && n<=amount;i--){
        for(int j = 1;j<=c && n<=amount;j++){
            cin>>map[i][j];
            n++;
        }
    }
    Row = r;
    Col = c;
}

void Map::printMap(int r,int c){
    cout<<"FINAL NAP:"<<endl;
    int n = 0;
    int amount = r*c;
    for(int i = 1000;i>=1 && n<=amount;i--){
        for(int j = 1;j<=c && n<=amount;j++){
            cout<<map[i][j];
            n++;
        }
    }
}

bool Map::isEmpty(){
    return 0;
}

void Map::lucky_clover(int now_r,int now_c,char input){
    if(input == '\0') return;
    if(isEmpty()) return;
    int max;
    for(int i = now_r;i>=1;i--){
        for(int j = now_c+2;j>=1&&j<=Col;j--){
            if(map[i][j]!='\0'){
                max = i;
                break;
            }
        }
    }
    max++;
    int count = 0;
    while (count<3)
    {
        for(int j = now_c-2;j>=1&&j<=Col;j++) map[max][j] = input;
        max++;
        count++;
    }
    Row+=3;
}

char Map::dig(int col){
    char answer;
    for(int i = 1;i<=Row;i++){
        if(map[i][col]!='\0'){
            answer = map[i][col];
            map[i][col] = '\0';
            return answer;
        }
    }
    return '\0';
    
}

int main(void){

}