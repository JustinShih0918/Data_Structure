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
## test case for reverse
5
Insert 1 1 1 Neutral
Insert 2 1 1 Neutral
Insert 3 1 1 Neutral
Insert 4 1 1 Neutral
Reverse 5
### code for change pointer of reverse
```C++
Node *tmp = target;
    Node *tail = tmp;
    Node *tmp2;
    for(int i = 0;i<range-1 && tmp->next!=target;i++) tmp = tmp->next;

    while (tail!=tmp->next)
    {
        tmp2 = tail->prev;
        tail->prev = tail->next;
        tail->next = tmp2;
        tail = tail->prev;
    }
    // cout<<"6's prev is "<<tmp->prev->prev->poke<<endl;
    // cout<<"6's next is "<<tmp->prev->prev->poke<<endl;
    // cout<<"tmp is "<<tmp->poke<<"\n";
    // cout<<"tmp prev is "<<tmp->prev->poke<<endl;
    // cout<<"tmp next is "<<tmp->next->poke<<endl;
    // cout<<"tail is "<<tail->poke<<"\n";
    // cout<<"tail prev is "<<tail->prev->poke<<endl;
    // cout<<"tail next is "<<tail->next->poke<<endl;
    tail->next->next = tmp;
    target = tmp;
    
    //printChain();
    //next state
    Node *first = tail->next;
    tail = first;
    while (first->next!=target && first!=target)
    {
        cout<<"in the while"<<endl;
        for(int i = 0;i<range-1 && tmp->next!=target;i++) first = first->next;
        while (tail!=first->next)
        {
            tmp2 = tail->prev;
            tail->prev = tail->next;
            tail->next = tmp2;
            tail = tail->prev;
        }
        cout<<"first is "<<first->poke<<"\n";
        cout<<"first prev is "<<first->prev->poke<<endl;
        cout<<"first next is "<<first->next->poke<<endl;
        cout<<"tail is "<<tail->poke<<"\n";
        cout<<"tail prev is "<<tail->prev->poke<<endl;
        cout<<"tail next is "<<tail->next->poke<<endl;
        tail->next->next = first;

        //next round
        first = tail->next;
        tail = first;
    }
```
