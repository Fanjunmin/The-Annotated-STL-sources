//filename 5set-test.cpp

#include <set>
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    int i;
    int ia[5] = { 0, 1, 2, 3, 4 };
    set<int> iset(ia, ia+5);

    cout << "size = " << iset.size() << endl;   //size = 5
    cout << "3 count = " << iset.count(3) << endl;  //3 count = 1

    iset.insert(3);
    cout << "size = " << iset.size() << endl;   //size = 5
    cout << "3 count = " << iset.count(3) << endl;  //3 count = 1

    iset.insert(5);
    cout << "size = " << iset.size() << endl;    //size = 6
    cout << "3 count = " << iset.count(3) << endl;  //3 count = 1

    iset.erase(1);
    cout << "size = " << iset.size() << endl;   //size = 5
    cout << "3 count = " << iset.count(3) << endl;  //3 count = 1
    cout << "1 count = " << iset.count(1) << endl;  //1 count = 0

    set<int>::iterator iter1 = iset.begin();
    set<int>::iterator iter2 = iset.end();
    for(; iter1 != iter2; ++iter1)
        cout << *iter1 << ' ';  //0 2 3 4 5
    cout << endl;

    iter1 = find(iset.begin(), iset.end(), 3);
    if(iter1 != iset.end())
        cout << "3 found" << endl;  //3 found

    iter1 = find(iset.begin(), iset.end(), 1);
    if(iter1 == iset.end())
        cout << "1 not found" << endl;  //1 not found

    iter1 = iset.find(3);
    if(iter1 != iset.end())
        cout << "3 found" << endl;  // 3 found

    iter1 = iset.find(1);
    if(iter1 == iset.end())
        cout << "1 not found" << endl;  // 1 found
    //set的成员函数find()要比STL find()快, 因为STL find()是循序查找，时间复杂度O(n);
    //*iter1 = 10;    //无法使用迭代器改变set元素
    return 0;
}
