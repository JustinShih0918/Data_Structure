#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
class Queue{
    public:
        Queue(int size);
        bool isEmpty();
        char Top();
        char Rear();
        void Push(char item);
        char Pop();
        void printQueue();
        bool isFull();
    private:
        int top;
        int rear;
        int capacity;
        char* queue;
        void doubleSize();
};

Queue::Queue(int size){
    top = 0;
    rear = 0;
    capacity = size;
    queue = new char[size];
    memset(queue,'\0',sizeof(char)*capacity);
}

void Queue::doubleSize(){
    capacity*=2;
    char* newQueue = new char[capacity];
    memset(newQueue,'\0',sizeof(char)*capacity);
    int j = -1;
    for (int i = top; i < rear; i++) {
        j++;
        newQueue[j] = queue[i];
    }
    top = 0;
    rear = j+1;
    delete [] queue;
    queue = newQueue;
}

bool Queue::isFull(){
    return (rear == capacity);
}

bool Queue::isEmpty(){
    return (top == rear);
}

void Queue::printQueue(){
    cout<<top<<" "<<rear<<"\n";
    cout<<"FINAL Tools:"<<"\n";
    if(isEmpty()) {
        cout<<"\n";
        return;
    }
    else{
        for(int i = top;i<rear;i++){
            cout<<queue[i]<<" ";
        }
        cout<<"\n";
    }
}

char Queue::Pop(){
    if(isEmpty()) return '\0';
    char answer = queue[top];
    queue[top] = '\0';
    top++;
    return answer;
}

void Queue::Push(char item){
    if(isFull()) doubleSize();
    queue[rear++] = item;
}
char Queue::Top(){
    return queue[top];
}
char Queue::Rear(){
    return queue[rear-1];
}

int main(void){
    Queue test(8);
    for(int i = 0;i<15;i++){
        test.Push(i+59);
    }
    for (int i = 0; i < 11; i++)
    {
        test.Pop();
    }
    for(int i = 0;i<15;i++){
        test.Push(i+59);
    }
    for (int i = 0; i < 11; i++)
    {
        test.Pop();
    }
    
    test.printQueue();
}

