#include <bits/stdc++.h>
#include <queue>
#include <vector>
#include <iostream>
using namespace std;

class Row{
public:
    vector<char> list;
    int top;
    int rightMost;
    Row(vector<char> c){
        list = c;
        updateRightMost();
        updateTop();
    }
    void updateRightMost(){
        for(int i = list.size()-1;i>=0;i--){
            if(list[i]!='_'){
                rightMost = i;
                break;
            }
        }
    }
    void updateTop(){
        for(int i = 0;i<list.size();i++){
            if(list[i]!='_'){
                top = i;
                break;
            }
        }
    }
    char pop_front(){
        updateTop();
        if(top == list.size()) return '_';
        char c = list[top];
        list[top] = '_';
        top++;
        return c;
    }
    void doButton(int mode, int pos){
        char target = (mode ? 'G' : 'D');
        for(int i = rightMost+1;i<pos;i++) list.push_back('_');
        list.push_back(target);
        rightMost = pos;
    }
    void printRow(){
        for(int i = 0;i<list.size();i++) cout << list[i] << " ";
        cout << "\n";
    }
};
class Map{
public:
    vector<Row> map;
    vector<char> inventory;
    vector<char> backpack;
    bool hasCoin = false;
    bool end = false;
    int digBefore = -1;
    Map(){}
    void Dig(int row){
        digBefore = row;
        char c = map[row].pop_front();
        if(c == 'G' || c == 'D') backpack.push_back(c);
        else if(c == 'S' || c == 'X') inventory.push_back(c);
        else if(c == 'C') hasCoin = true;
        else if(c == 'V') Virus();
        else if(c == 'P') Pig();
    }
    void Use(){
        if(inventory.empty()) return;

        char c = inventory.back();
        inventory.pop_back();

        if(c == 'S'){
            Dig(digBefore);
            Dig(digBefore);
        }
        else if(c == 'X') Button();
    }
    int findRightMost(){
        int max = -1;
        for(int i = 0;i<map.size();i++){
            map[i].updateRightMost();
            if(map[i].rightMost > max){
                max = map[i].rightMost;
            }
        }
        return max;
    }
    void Button(){
        int pos = findRightMost() + 1;
        for(int i = 0;i<map.size();i++){
            map[i].doButton(i%2,pos);
        }
    }
    void printInventory(){
        cout << "Inventory:";
        for(int i = 0;i<inventory.size();i++){
            cout << " " << inventory[i];
        }
        cout << "\n";
    }
    void printBackpack(){
        cout << "Backpack:";
        for(int i = 0;i<backpack.size();i++){
            if(backpack[i] != '_') cout << " " << backpack[i];
        }
        cout << "\n";
    }
    void printMap(){
        cout << "Map:\n";
        for(int i = 0;i<map.size();i++){
            map[i].printRow();
        }
    }

    void Virus(){
        end = true;
        cout << "Game Over!\n";
        printAns();
    }

    void Pig(){
        if(hasCoin) {
            cout << "Ding!\n";
            hasCoin = false;
            return;
        }
        for(int i = 0;i<backpack.size();i++){
            if(backpack[i] == 'G') backpack[i] = '_';
        }
    }
    void printAns(){
        printBackpack();
        printInventory();
        printMap();
    }
};


int main(){
    int R,L,N;
    cin >> R >> L >> N;
    Map play;
    for(int i = 0;i<L;i++){
        vector<char> tmp;
        for(int j = 0;j<R;j++){
            char c;
            cin >> c;
            tmp.push_back(c);
        }
        play.map.push_back(Row(tmp));
    }

    for(int i = 0;i<N;i++){
        string command;
        int row;
        cin >> command;
        if(command == "USE") play.Use();
        else if(command == "DIG"){
            cin >> row;
            play.Dig(row);
            if(play.end) return 0;
            
        }
    }
    play.printAns();
}

