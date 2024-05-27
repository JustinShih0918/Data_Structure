#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <algorithm>
using namespace std;

class Game{
    public:
        int operation;
        Game(int N) : operation(0){
            data.resize(N+1);
            data[0] = 0;
        }
        vector<int> data;
        int partition(int left, int right){
            int pivot = data[left + (right - left) / 2];
            int i = left;
            int j = right;
            while (i <= j)
            {
                while (data[i] < pivot) i++;
                while (pivot < data[j]) j--;
                if(i <= j){
                    if(j - i == 1){
                        operation++;
                        int tmp = data[i];
                        data[i] = data[j];
                        data[j] = tmp;
                    }
                    i++;
                    j--;
                }
            }
            return i;
        }
        using segment = pair<vector<int>,int>;
        void quickSort(int left, int right){
            if(left < right){
                int pivot = partition(left,right);
                quickSort(left, pivot - 1);
                quickSort(pivot, right);
            }
        }
        void boubleSort(){
            int len = data.size();
            for(int i = 1; i<len;i++){
                for(int j = 1;j<len-1;j++){
                    if(data[j] > data[j+1]){
                        int tmp = data[j];
                        data[j] = data[j+1];
                        data[j+1] = tmp;
                        operation++;
                    }
                }
            }
        }
        vector<segment> big;
        void mergeSort(){
            int len = data.size();
            for(int i = 1;i<=len-1;i+=2){
                vector<int> seg;
                if(i+1 <= len-1){
                    if(data[i] > data[i+1]){
                        operation++;
                        seg.push_back(data[i+1]);
                        seg.push_back(data[i]);
                    }
                    else{
                        seg.push_back(data[i]);
                        seg.push_back(data[i+1]);
                    }
                }
                else seg.push_back(data[i]);
                big.push_back(segment(seg,seg.size()));
            }

        }
        void printData(){
            for(int i = 1;i<data.size();i++) cout << data[i] << " ";
            cout << "\n";
        }
        int cmp(const int a,const int b){
            if(a < b) return 1;
            else return 0;
        }
};

int main(void){
    int N;
    cin >> N;
    Game game(N);
    for(int i = 1;i<=N;i++){
        int a;
        cin >> a;
        game.data[a] = i;
    }
    //game.printData();
    int i = N;
    while (game.data[i]!=i && i>=1)
    {
        game.quickSort(1,i);
        game.printData();
        if(game.data[i] == i) i--;
    }
    game.quickSort(1,N);
    game.printData();
    cout << game.operation << "\n";
}