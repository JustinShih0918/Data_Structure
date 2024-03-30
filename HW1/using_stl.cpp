#include <iostream>
#include <queue>
#include <stack>
#include <cstdio>
#include <cstring>

using namespace std;

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
    stack<char> bag;
    queue<char> tools;
    char movement[3];
    while (N--)
    {
        scanf("%s",movement);
        if(movement[0] == 'D'){
            int col;
            cin>>col;
            col++;
            char dig = miner.dig(col);
            miner.updateRow();
            if(dig == 'D'||dig == 'G') bag.push(dig);
            else if(dig == 'B') miner.bomb(miner.getDig_row(),col);
            else if(dig == 'C') miner.lucky_clover(col,bag.top());
            else if(dig == 'P') while (bag.top()!='D'&&!bag.empty()) bag.pop(); 
            else if (dig == 'M'||dig == 'F') tools.push(dig);
            miner.updateRow();
            // miner.printMap();
            //tools.printQueue();
            // bag.printStack();
        }else if(movement[0] == 'U'){
            char use_tool = tools.front();
            tools.pop();
            if(use_tool == 'F') miner.flashlight();
            else if(use_tool == 'M'){
                for(int i = 1;i<=R;i++){
                    char dig = miner.dig(i);
                    miner.updateRow();
                    if(dig == 'G' || dig == 'D') bag.push(dig);
                    else if(dig == 'B') miner.bomb(miner.getDig_row(),i);
                    else if(dig == 'C') miner.lucky_clover(i,bag.top());
                    else if(dig == 'P') while (bag.top()!='D'&&!bag.empty()) bag.pop(); 
                    else if (dig == 'M'||dig == 'F') tools.push(dig);
                    miner.updateRow();
                }
                miner.updateRow();
            }
            // miner.printMap();
            // tools.printQueue();
            // bag.printStack();
        }
    }
    cout<<"FINAL BAG:"<<"\n";
    if(bag.empty()) cout<<"\n";
    else{
        while (!bag.empty())
        {
            cout<<bag.top()<<" ";
            bag.pop();
        }
        cout<<"\n";
    }
    
    miner.printMap();
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