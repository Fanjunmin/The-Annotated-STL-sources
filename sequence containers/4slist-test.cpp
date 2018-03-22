//4.9.5 slist元素操作
//filename: 4slist-test

#include <slist>    //不在标准规范里面
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    int i;
    slist<int> islist;
    cout << "size = " << islist.size() << endl; //size = 0

    islist.push_front(9);
    islist.push_front(1);
    islist.push_front(2);
    islist.push_front(3);
    islist.push_front(4);
    cout << "size = " << islist.size() << endl; //size = 5

    auto ite = illist.begin(), ite2 = islist.end();
    for(; ite != ite2; +=ite)
        cout << *ite << ' ';    //9 1 2 3 4
    cout << endl;

    ite = find(islist.begin(), islist.end(), 1);
    if(ite != ite2)
        islist.insert(ite, 99);
    cout << "size = " << islist.size() << endl; //size = 6
    cout << *ite << endl;   //99

    for(ite = islist.begin(); ite != ite2; +=ite)
        cout << *ite << ' ';    //9 1 99 2 3 4
    cout << endl;

    ite = find(islist.begin(), islist.end(), 3);
    if(ite != ite2)
        cout << *(islist.erase(ite)) << endl;   //3

    for(ite = islist.begin(); ite != ite2; +=ite)
        cout << *ite << ' ';    //9 1 99 2 4
    cout << endl;
}
