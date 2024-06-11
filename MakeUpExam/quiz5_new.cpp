#include <bits/stdc++.h>
#include <iostream>
using namespace std;
long long ans = 0;

class Node{
public:
    Node *left;
    Node *right;
    long long val;
    long long rightTreeSize;
    Node(long long v) : val(v), rightTreeSize(0){
        left = NULL;
        right = NULL;
    }
};

class Tree{
public:
    Node *root;
    Tree(){
        root = NULL;
    }
    void insert(long long val, Node* head){
        if(root == NULL){
            root = new Node(val);
            return;
        }

        if(head!=NULL){
            if(head->val < val){
                head->rightTreeSize++;
                if(head->right){
                    insert(val,head->right);
                }
                else head->right = new Node(val);
            }
            else if(head->val > val){
                ans += head->rightTreeSize + 1;
                if(head->left){
                    insert(val,head->left);
                }
                else head->left = new Node(val);
            }
        }
    }
};

int main(void){
    long long n;
    cin >> n;
    Tree tree;
    for(long long i = 0;i<n;i++){
        long long a;
        cin >> a;
        tree.insert(a,tree.root);
    }
    cout << ans << "\n";
}