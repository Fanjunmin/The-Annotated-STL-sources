//4.6.4 以list作为queue的底层容器的配接器
//filename : 4queue-test.cpp

#include <queue>
#include <list>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
int main()
{
    queue <int, list<int>> iqueue;
    //无法使用vector<int>代替list<int>和deque<int>，由于vector并没有pop_front()成员函数
    iqueue.push(1);
    iqueue.push(3);
    iqueue.push(5);
    iqueue.push(7);

    cout << "size = " << iqueue.size() << endl;     //size = 4
    cout << iqueue.front() << endl;       //1

    iqueue.pop();   cout << iqueue.front() << endl;   //3
    iqueue.pop();   cout << iqueue.front() << endl;   //5
    iqueue.pop();   cout << iqueue.front() << endl;   //7

    cout << iqueue.size() << endl;          //1
    return 0;
}
