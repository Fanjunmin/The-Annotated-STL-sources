//4.5.3 以list作为stack的底层容器的配接器
//filename :4stack-test.cpp


#include <stack.h>
#include <iostream>
#include <list>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
    typedef stack<int, vector<int>/*list<int> 默认是deque<int>*/> myStack;
    myStack istack;
    istack.push(1);
    istack.push(3);
    istack.push(5);
    istack.push(7);

    cout << "size = " << istack.size() << endl;     //size = 4
    cout << istack.top() << endl;       //7

    istack.pop();   cout << istack.top() << endl;   //5
    istack.pop();   cout << istack.top() << endl;   //3
    istack.pop();   cout << istack.top() << endl;   //1

    cout << istack.size() << endl;          //1
    return 0;
}
