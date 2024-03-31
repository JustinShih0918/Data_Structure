#include <iostream>
#include <vector>
#include <string>
using namespace std;
vector<vector<char> > space(15,vector<char>(15,0));

void insert(string input,int row);
void shift(int row,char add,int len);
void reverse(int row,int len);
void print(int amount,int n);
void transpose(int amount,int n);

int main(void){

    string command;
    string input;
    int input_len;
    int row;
    char add;
    int i = 0;
    while (cin>>command && !cin.eof())
    {
        switch (command[0])
        {
        case 'I':
            cin>>input;
            insert(input,i);
            input_len = input.length();
            i++;
            break;
        case 'S':
            cin>>row>>add;
            shift(row,add,input_len);
            break;
        case 'R':
            cin>>row;
            reverse(row,input_len);
            break;
        case 'T':
            transpose(i,input_len);
            break;
        case 'P':
            print(i,input_len);
            break;
        }
    }
}

void insert(string input,int row){
    for(int i = 0;i<(int)input.length();i++){
        space[row][i] = input[i];
    }
}
void shift(int row,char add,int len){
    space[row].erase(space[row].begin(),space[row].begin()+1);
    space[row][len-1] = add;
}
void reverse(int row,int len){
    for(int i = 0;i<len/2;i++){
        char tmp = space[row][i];
        space[row][i] = space[row][len-i-1];
        space[row][len-i-1] = tmp;
    }
}
//void transpose(int row);
void print(int amount,int n){
    for(int i = 0;i<amount;i++){
        for(int j = 0;j<n;j++){
            cout<<space[i][j]<<" ";
        }
        cout<<"\n";
    }
}

void transpose(int amount,int n){
    for(int i = 0;i<n;i++){
        for(int j = 0;j<amount;j++){
            cout<<space[j][i]<<" ";
        }
        cout<<"\n";
    }
}




