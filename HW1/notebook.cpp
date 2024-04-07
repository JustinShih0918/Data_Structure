#include <utility>
#include <iostream>
#include <string>
#include <vector>
#include <deque>
using namespace std;

int main()
{
    vector<pair<string,int> > space(10);
    pair<int, int> p(10, 10);

    deque<int> dq;
    dq.push_back(10);
    dq.pop_back();
    dq.push_front(10);
    dq.push_front(10);
}