#include <iostream>
#include <cstdio>
#include <vector>
#include <deque>
#include <stack>
#include <queue>
#include <string>
#include <cstring>
using namespace std;

class Map{
    public:
        Map(int row_number,int col_number);
        bool isEmpty();
        char Dig(int row);
        void strange_button();
        void virus();
        void printMap();
    private:
        char map[1005][1005];
        int Row;
        int Col;
        int dig_row;
        int dig_col;
};

bool coin = false;

int main(void){
    int R,L,N;
    cin>>R>>L>>N;
    Map miner(L,R);
    deque<char> backpack;
    deque<char> inventory;
    int back_amount = 0;
    int inventory_amount = 0;
    string command;
    int row;
    while (N--)
    {
        cin>>command;
        if(command[0] == 'D'){
            cin>>row;
            row++;
            char dig_item = miner.Dig(row);
            if(dig_item == 'D' || dig_item == 'G') {
                backpack.push_back(dig_item);
                back_amount++;
            }
            else if(dig_item == 'S' || dig_item == 'X') {
                inventory.push_back(dig_item);
                inventory_amount++;
            }
            else if(dig_item == 'C') coin = true;
            else if(dig_item == 'V'){
                miner.virus();
                return 0;
            }
            else if(dig_item == 'P'){
                if (coin){
                    coin = false;
                    cout<<"Ding!\n";
                }
                else if(!backpack.empty()){
                    for(int i = 0;i<backpack.size();i++){
                        if(backpack[i] == 'G') {
                            backpack.erase(backpack.begin()+i,backpack.begin()+i+1);
                            back_amount--;
                        }
                    }
                }
            }
            // miner.printMap();
            // cout<<"Backpack: ";
            // for(int i = 0;i<(int)backpack.size();i++) cout<<backpack[i]<<" ";
            // cout<<"\n";

            // cout<<"Inventory: ";
            // for (int i = 0; i < inventory.size(); i++) cout<<inventory[i]<<" ";
            // cout<<"\n";
        }
        if(command[0] == 'U'){
            char use_item = '\0';
            if(!inventory.empty()){
                use_item = inventory.back();
                inventory_amount--;
                inventory.pop_back();
            }
            if(use_item == 'S'){
                int n = 2;
                while (n--)
                {
                    char dig_item = miner.Dig(row);
                    if(dig_item == 'D' || dig_item == 'G') {
                        backpack.push_back(dig_item);
                        back_amount++;
                    }
                    else if(dig_item == 'S' || dig_item == 'X') {
                        inventory.push_back(dig_item);
                        inventory_amount++;
                    }
                    else if(dig_item == 'C') coin = true;
                    else if(dig_item == 'V'){
                        miner.virus();
                        return 0;
                    }
                    else if(dig_item == 'P'){
                        if (coin){
                            coin = false;
                            cout<<"Ding!\n";
                        }
                        else if(!backpack.empty()){
                            for(int i = 0;i<(int)backpack.size();i++){
                                if(backpack[i] == 'G') {
                                    backpack.erase(backpack.begin()+i,backpack.begin()+i+1);
                                    back_amount--;
                                }
                            }
                        }
                    }
                }
            }
            else if(use_item == 'X') miner.strange_button();
            //miner.printMap();
            // cout<<"Backpack: ";
            // for(int i = 0;i<(int)backpack.size();i++) cout<<backpack[i]<<" ";
            // cout<<"\n";

            // cout<<"Inventory: ";
            // for (int i = 0; i < inventory.size(); i++) cout<<inventory[i]<<" ";
            // cout<<"\n";
        }
    }
    cout<<"Backpack:";
    for(int i = 0;i<back_amount;i++) cout<<" "<<backpack[i];
    cout<<"\n";

    cout<<"Inventory:";
    for (int i = 0; i < inventory_amount; i++) cout<<" "<<inventory[i];
    cout<<"\n";

    miner.printMap();
}

Map::Map(int row_number,int col_number){
    memset(map,'_',sizeof(map));
    for(int i = 1;i<=row_number;i++){
        for(int j = 1;j<=col_number;j++){
            cin>>map[i][j];
        }
    }
    Row = row_number;
    Col = col_number;
    dig_row = -1;
}

bool Map::isEmpty(){
    for(int i = Col;i>=1;i--){
        for(int j = 1;j<=Row;j++){
            if(map[j][i]!='_') return false;
        }
    }
    return true;
}
char Map::Dig(int row){
    for(int i = 1;i<=Col;i++){
        if(map[row][i]!='_'){
            char answer = map[row][i];
            map[row][i] = '_';
            dig_row = row;
            dig_col = i;
            return answer;
        }
    }
    dig_row = row;
    dig_col = 1;
    return '_';
}
void Map::strange_button(){
    for(int i = 1;i<=Row;i++){
        if(i%2 == 0) map[i][Col+1] = 'G';
        else if(i%2!=0) map[i][Col+1] = 'D';
    }
    Col++;
}
void Map::virus(){
    cout<<"Game Over!\n";
    printMap();
}

void Map::printMap(){
    cout<<"Map:\n";
    for(int i = 1;i<=Row;i++){
        for(int j = 1;j<=Col;j++){
            cout<<map[i][j]<<" ";
        }
        cout<<"\n";
    }
}


