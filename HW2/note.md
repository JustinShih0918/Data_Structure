## check n^2 method
```C++
Node* tmp = target;
    Node* tmp2;
    Node* pre;
    bool delete_it = false;
    for(int i = 0;i<range;i++){
        if(isEmpty()) break;
        tmp2 = tmp->next;
        for(int j = 0;j<range-i-1;j++){
            if(isEmpty()) break;
            if(tmp->poke == tmp2->poke){
                if(tmp2 == target){
                    //cout<<"delete target:"<<tmp2->poke<<"\n";
                    deleteTarget(); //check
                }
                else{
                    //cout<<"delete:"<<tmp2->poke<<"\n";
                    pre = tmp2->prev;
                    deleteNode(tmp2);
                    tmp2 = pre;
                    delete_it = true;
                }
            }
            tmp2 = tmp2->next;
        }
        if(delete_it){
            if(tmp == target){
                //cout<<"delete_it target:"<<tmp->poke<<"\n";
                deleteTarget();
                tmp = target;
            }
            else{
                //cout<<"delete_it:"<<tmp->poke<<"\n";
                pre = tmp->prev;
                deleteNode(tmp);
                tmp = pre;
                tmp = tmp->next;
            }
            delete_it = false;
            i++;
        }
        else tmp = tmp->next;
    }
```