#include <string>
#include <iostream>
using namespace std;

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

int main(){
    Node* a = new Node(0,0,0,"");
    Node* b = new Node(0,0,0,"");
    bool i = (a==b);
    cout<<i;
}