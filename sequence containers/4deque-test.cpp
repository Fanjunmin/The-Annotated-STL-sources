//4.4.5 deque的构造与内存管理
//filename ：4deque-test.cpp

#include <deque>
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    //deque<int, alloc, 8> ideq(20, 9);
    //error: 'alloc' was not declare in this scope
    //error: wrong number for 'template<class _Tp, class _Alloc>' class std::deque
    //stl_deque注释：
    /*
    * In previous versions of deque, there was an extra template
    * parameter so users could control the node size.  This extension
    * turns out to violate the C++ standard (it can be detected using
    * template template parameters), and it has been removed.
    */
    //无法在指定第三个参数也就是缓冲区的大小

    deque<int, std::allocator<int> > ideq(20, 9);
    cout << "size = " << ideq.size() << endl;

    for(int i = 0; i < ideq.size(); ++i)
        ideq[i] = i;

    for(int i = 0; i < ideq.size(); ++i)
        cout << ideq[i] << ' ';
    cout << endl;

    for(int i = 0; i < 3; ++i)
        ideq.push_back(3);

    for(int i = 0; i < ideq.size(); ++i)
        cout << ideq[i] << ' ';
    cout << endl;
    cout << "size = " << ideq.size() << endl;

    ideq.push_back(3);
    for(int i = 0; i < ideq.size(); ++i)
        cout << ideq[i] << ' ';
    cout << endl;
    cout << "size = " << ideq.size() << endl;

    ideq.push_back(99);
    for(int i = 0; i < ideq.size(); ++i)
        cout << ideq[i] << ' ';
    cout << endl;
    cout << "size = " << ideq.size() << endl;

    ideq.push_front(98);
    ideq.push_front(97);
    for(int i = 0; i < ideq.size(); ++i)
        cout << ideq[i] << ' ';
    cout << endl;
    cout << "size = " << ideq.size() << endl;

    auto ite = find(ideq.begin(), ideq.end(), 3);
    cout << *ite << endl;

    //cout << *(ite.cur) << endl;
    //无法通过编译，由于缓冲区的现行元素并非书中cur,而是_M_cur;

    cout << *(ite._M_cur) << ' ' << *(ite._M_node) << endl;

    //下列*(ideq.begin())._M_first 大概率输出一个垃圾值
    cout << *(ideq.begin())._M_first << ' ' << *(ideq.begin())._M_cur << endl;

    return 0;
}
