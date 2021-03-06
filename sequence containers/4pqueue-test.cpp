//优先队列测试
//filename:4pqueue-test.cpp
#include <queue>
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    int ia[9] = {0, 1, 2, 3, 4, 8, 9, 3, 5};
    priority_queue<int, vector<int>> ipq(ia, ia+9); //以vector为底层容器
    cout << "size = " << ipq.size() << endl;    //size = 9;
    for(int i = 0; i < 9; ++i)
        cout << ipq.top() << ' ';   //9 9 9 9 9 9 9 9 9
    cout << endl;

    while(!ipq.empty()) {
        cout << ipq.top() << ' ';   //9 8 5 4 3 3 2 1 0
        ipq.pop();
    }
    cout << endl;
    return 0;
}
