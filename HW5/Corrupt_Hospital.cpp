#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Date{
    public:
        int year;
        int month;
        int day;
        Date(int y,int m,int d){
            year = y;
            month = m;
            day = d;
        }
        Date() : year(0), month(0), day(0){}
};

class Person{
    public:
        Person(int idx,string nn,int Age,int Money,int mem,string dDate){
            name = nn;
            age = Age;
            money = Money;
            if(mem == 1) memberShip = true;
            else memberShip = false;
            date = parseDate(dDate);
            index = idx;
        }
        Person(){}
        string name;
        int age;
        int money;
        bool memberShip;
        struct Date date;
        int index;
        Date parseDate(string n){
            int year,month,day;
            if(!memberShip){
                year = 0;
                month = 0;
                day = 0;
            }
            else{
                year = (n[0]-'0')*1000 + (n[1]-'0')*100 + (n[2]-'0')*10 + (n[3]-'0');
                month = (n[5]-'0')*10 + (n[6]-'0');
                day = (n[8]-'0')*10 + (n[9]-'0');
            }
            return Date(year,month,day);
        }
};

class Hospital{
    public:
        int order;
        int pPandan;
        int kBear;
        vector<Person> people;
        Hospital() : order(0){}
        void Routine(int day){
            quickSort(0,people.size()-1,1);
            printAll();
            OutputAns(pPandan,day);
            quickSort(0,people.size()-1,2);
            Sent(kBear);
        }
        void addPerson(Person p){
            people.push_back(p);
            order++;
        }
        int partitionP(int left,int right){
            Person pivot = people[left + (right - left) / 2];
            int i = left;
            int j = right;
            Person tmp;
            while (i <= j)
            {
                while (compareP(people[i],pivot)) i++;
                while (compareP(pivot,people[j])) j--;
                if(i <= j){
                    tmp = people[i];
                    people[i] = people[j];
                    people[j] = tmp;
                    i++;
                    j--;
                }
            }
            return i;
        }
        int partitionB(int left,int right){
            Person pivot = people[left + (right - left) / 2];
            int i = left;
            int j = right;
            Person tmp;
            while (i <= j)
            {
                while (compareB(pivot,people[i])) i++;
                while (compareB(pivot,people[j])) j--;
                if(i <= j){
                    tmp = people[i];
                    people[i] = people[j];
                    people[j] = tmp;
                    i++;
                    j--;
                }
            }
            return i;
        }
        void quickSort(int left,int right,int mode){
            if(left < right){
                int pivotIndex;
                if(mode == 1) pivotIndex = partitionP(left,right);
                else pivotIndex = partitionB(left,right);
                quickSort(left,pivotIndex-1,mode);
                quickSort(pivotIndex,right,mode);
            }
        }
        bool compareP(const Person &a, const Person &b){
            if(a.memberShip && !b.memberShip) return true;
            else if(!a.memberShip && b.memberShip) return false;
            else{
                if(a.memberShip && b.memberShip){
                    if(a.date.year < b.date.year) return true;
                    else if(a.date.year > b.date.year) return false;
                    else{
                        if(a.date.month < b.date.month) return true;
                        else if(a.date.month > b.date.month) return false;
                        else{
                            if(a.date.day < b.date.day) return true;
                            else if(a.date.day > b.date.day) return false;
                            else{
                                int cmp = a.name.compare(b.name);
                                if(cmp < 0) return true;
                                else if(cmp > 0) return false;
                                else if(cmp == 0){
                                    if(a.index < b.index) return true;
                                    else if(a.index > b.index) return false;
                                    else return false;
                                }
                            }
                        }
                    }
                }
                else{
                    int cmp = a.name.compare(b.name);
                    if(cmp < 0) return true;
                    else if(cmp > 0) return false;
                    else if(cmp == 0){
                        if(a.index < b.index) return true;
                        else if(a.index > b.index) return false;
                        else return false;
                    }
                }
            }
            return false;
        }
        bool compareB(const Person &a, const Person &b){
            if(a.money > b.money) return true;
            else if(a.money < b.money) return false;
            else{
                if(a.index < b.index) return true;
                else if(a.index > b.index) return false;
                else return false;
            }
        }
        void Sent(int range){
            int len = people.size();
            for(int i = 0;i<range && i<len;i++){
                people.erase(people.begin());
            }
        }
        void OutputAns(int range,int day){
            cout << "DAY #"<< day << "\n";
            int inc = 0;
            int len = people.size();
            for(int i = 0;i<range && i< len;i++){
                cout << people[0].name << " " << people[0].age << "\n";
                inc += people[0].money*0.9;
                people.erase(people.begin());
            }
            cout << "INCOME TODAY: "<<inc << "\n";
        }
        void printOne(int index){
            Person p = people[index];
            cout << p.name << "\n";
            cout << "(age,money,index): " << p.age << " "<<p.money << " "<<p.index<<" "<< "\n";
            if(p.memberShip) cout << p.date.year << "-" << p.date.month << "-" << p.date.day <<"\n";
            else cout << p.date.year << "\n";
        }
        void printAll(){
            int len = people.size();
            for(int i = 0;i<len;i++) printOne(i);
        }
};

int main(void){
    int N,M;
    cin >> N >> M;
    cin.get();
    Hospital Panda;
    for(int i = 0;i<N;i++){
        string Name,Date;
        int age,money,membership;
        getline(cin,Name);
        cin >> age >> money >> membership;
        cin >> Date;
        cin.get();
        Person p(Panda.order,Name,age,money,membership,Date);
        Panda.addPerson(p);
    }
    for (int i = 1; i <= M ; i++){
        int P,X,K;
        cin >> P >> X >> K;
        cin.get();
        Panda.pPandan = X;
        Panda.kBear = K;
        for(int j = 0;j<P;j++){
            string Name,Date;
            int age,money,membership;
            getline(cin,Name);
            cin >> age >> money >> membership;
            cin >> Date;
            cin.get();
            Person p(Panda.order,Name,age,money,membership,Date);
            Panda.addPerson(p);
        }
        Panda.Routine(i);
    }
}
