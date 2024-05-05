#include <bits/stdc++.h>
#include <iostream>
using namespace std;
const string mode_pre = "pre";
const string mode_in = "in";
const string mode_post = "post";
const string com_insert = "Insert";
const string com_delete = "Delete";
const string com_print = "Print";
const string com_max = "Max";
const string com_merge = "Merge";
const string com_disjoint = "Disjoint";
class Node{
    public:
        int value;
        Node* left;
        Node* right;
        Node* parent;
        Node(int v){
            value = v;
            left = NULL;
            right = NULL;
            parent = NULL;
        }
        void deleteChild(Node* target){
            if(this->left == target) this->left = NULL;
            else if(this->right == target) this->right = NULL;
        }
    friend class Tree;
};

class Tree{
    public:
        Node* root;
        vector<Node*> child;
        int max;
        Tree(){
            child.resize(105,NULL);
            root = NULL;
            max = -2e9;
        }
        void setMax(){
            for(int i = 0;i<105;i++){
                if(child[i]){
                    if(child[i]->value>max) max = child[i]->value;
                }
            }
        }
        void insert(int par,int val){
            Node* nw = new Node(val);
            child[val] = nw;
            if(root == NULL){
                root = nw;
                nw->parent = NULL;
            }
            else if(child[par]){
                if(!child[par]->left){
                    child[par]->left = nw;
                    nw->parent = child[par];
                }
                else if(!child[par]->right){
                    child[par]->right = nw;
                    nw->parent = child[par];
                }
                else return;
            }
            if(val>max) max = val;
        }
        void delete_op(Node* root_here){
            if(root_here!=NULL){
                delete_op(root_here->left);
                delete_op(root_here->right);
                child[root_here->value] = NULL;
                if(root_here == root) root = NULL;
                if(root_here->value == max) max = -2e9;
                delete root_here;
            }
        }
        void deleteNode(int val){
            if(!child[val]) return;
            if(child[val]->parent) child[val]->parent->deleteChild(child[val]);
            delete_op(child[val]);
            setMax();
        }
        void inorder(Node* root_here){
            if(root_here!=NULL){
                inorder(root_here->left);
                cout<<root_here->value<<" ";
                inorder(root_here->right);
            }
            else return;
        }
        void postorder(Node* root_here){
            if(root_here!=NULL){
                postorder(root_here->left);
                postorder(root_here->right);
                cout<<root_here->value<<" ";
            }
        }
        void perorder(Node* root_here){
            if(root_here!=NULL){
                cout<<root_here->value<<" ";
                perorder(root_here->left);
                perorder(root_here->right);
            }
        }
        void print(string mode){
            if(root == NULL){
                cout<<"\n";
                return;
            }
            if(mode == mode_in) inorder(root);
            else if(mode == mode_pre) perorder(root);
            else if(mode == mode_post) postorder(root);
            cout<<"\n";
        }
        void print_max(){
            if(root) cout<<max<<"\n";
        }
        void setSubtree(Tree& sub,int mode){
            if(mode == 1) root->left = sub.root;
            else if(mode == 2) root->right = sub.root;
            if(sub.root == NULL) return;
            sub.root->parent = this->root;
            for(int i = 0;i<105;i++){
                if(sub.child[i]){
                    this->child[i] = sub.child[i];
                }
            }
            if(sub.max>this->max) this->max = sub.max;
        }
        void setDisjoint(Node* root_here){
            if(root_here!=NULL){
                child[root_here->value] = root_here;
                setDisjoint(root_here->left);
                setDisjoint(root_here->right);
            }
        }
};

int main(void){
    int n,ops;
    cin>>n>>ops;
    vector<Tree> forest(10);
    while (ops--)
    {
        string command;
        cin>>command;
        if(command == com_insert){
            int index,par,val;
            cin>>index>>par>>val;
            forest[index].insert(par,val);
        }
        else if(command == com_delete){
            int index,val;
            cin>>index>>val;
            forest[index].deleteNode(val);
        }
        else if(command == com_print){
            int index;
            string mode;
            cin>>index>>mode;
            forest[index].print(mode);
        }
        else if(command == com_max){
            int index;
            cin>>index;
            forest[index].print_max();
        }
        else if(command == com_merge){
            int dest,from,val;
            cin>>dest>>from>>val;
            Tree apple = Tree();
            apple.insert(0,val);
            apple.setSubtree(forest[dest],1);
            apple.setSubtree(forest[from],2);
            forest[from] = Tree();
            forest[dest] = apple;
        }
        else if(command == com_disjoint){
            int index,val;
            cin>>index>>val;
            bool found = false;
            if(forest[index].child[val]){
                found = true;
            }
            if(found){
                int i = 0;
                for(;i<n;i++){
                if(forest[i].root == NULL) break;
                }
                if(i == n){
                    forest.push_back(Tree());
                    n++;
                }
                Tree apple = Tree();
                if(forest[index].root->value == val){
                    forest[i] = forest[index];
                    forest[index] = apple;
                }
                else{
                    apple.root = forest[index].child[val];
                    apple.setDisjoint(forest[index].child[val]);
                    forest[index].child[val]->parent->deleteChild(forest[index].child[val]);
                    forest[i] = apple;
                }
            }
        }
    }
    for(int i = 0;i<n;i++){
        cout<<"Tree "<<i<<"\n";
        forest[i].print(mode_in);
    }
    
}
