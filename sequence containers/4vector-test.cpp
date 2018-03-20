//4.2.5 vector的构造和内存管理
//filename: 4vector-test.cpp

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    int i;
    vector<int, std::allocator<int>> iv(2, 9);
    cout << "初始元素为:" << endl;
    for(auto i : iv)
        cout << i << ' ';
    cout << endl;
    cout << "size = " << iv.size() << endl;         //size = 2
    cout << "capacity = " << iv.capacity() << endl; //capacity = 2

    iv.push_back(1);
    cout << "push_back(1):" << endl;
    cout << "size = " << iv.size() << endl;         //size = 3
    cout << "capacity = " << iv.capacity() << endl; //capacity = 4

    iv.push_back(2);
    cout << "push_back(2):" << endl;
    cout << "size = " << iv.size() << endl;         //size = 4
    cout << "capacity = " << iv.capacity() << endl; //capacity = 4

    iv.push_back(3);
    cout << "push_back(3):" << endl;
    cout << "size = " << iv.size() << endl;         //size = 5
    cout << "capacity = " << iv.capacity() << endl; //capacity = 8

    iv.push_back(4);
    cout << "push_back(4):" << endl;
    cout << "size = " << iv.size() << endl;         //size = 6
    cout << "capacity = " << iv.capacity() << endl; //capacity = 8

    iv.push_back(5);
    cout << "push_back(5):" << endl;
    cout << "size = " << iv.size() << endl;         //size = 7
    cout << "capacity = " << iv.capacity() << endl; //capacity = 8

    for(auto i : iv)
        cout << i << ' ';                           //9 9 1 2 3 4 5
    cout << endl;

    //以上说明了vector的扩容策略是倍加扩容(2倍),VC++是1.5倍

    iv.pop_back();
    iv.pop_back();
    cout << "两次pop_back()之后：" << endl;
    cout << "size = " << iv.size() << endl;         //size = 5
    cout << "capacity = " << iv.capacity() << endl; //capacity = 8

    iv.pop_back();
    cout << "一次pop_back()之后：" << endl;
    cout << "size = " << iv.size() << endl;         //size = 4
    cout << "capacity = " << iv.capacity() << endl; //capacity = 8

    auto ivite = find(iv.begin(), iv.end(), 1);
    if(ivite != iv.end()) iv.erase(ivite);
    cout << "删除一个元素1之后：" << endl;
    cout << "size = " << iv.size() << endl;         //size = 3
    cout << "capacity = " << iv.capacity() << endl; //capacity = 8
    for(auto i : iv)
        cout << i << ' ';                           //9 9 2
    cout << endl;

    ivite = find(iv.begin(), iv.end(), 2);
    if(ivite != iv.end())   iv.insert(ivite, 6, 7); //插入6个7
    cout << "插入6个元素7,7,7,7,7,7之后：" << endl;
    cout << "size = " << iv.size() << endl;         //size = 9
    cout << "capacity = " << iv.capacity() << endl; //capacity = 9
    for(auto i : iv)
        cout << i << ' ';                           //9 9 7 7 7 7 7 7 2
    cout << endl;

    iv.insert(iv.end() - 1, 7, 7);
    cout << "size = " << iv.size() << endl;         //size = 0
    cout << "capacity = " << iv.capacity() << endl; //capacity = 9

    iv.clear();
    cout << "size = " << iv.size() << endl;         //size = 0
    cout << "capacity = " << iv.capacity() << endl; //capacity = 9


    //以上说明了删除元素并不会改变capacity;
    //如果插入之前size < capacity，插入元素之后，capacity = max(capacity, new size)
    //如果插入之前恰好size == capacity， 插入多个元素之后，capacity = max(2*capacity, new size);
    return 0;
}
