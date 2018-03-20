//3.4.5 仿真测试tag types继承关系带来的影响
//filename:3tag-test.cpp
#include <iostream>
using namespace std;

struct B { };       //可当作InputIterator
struct D1 : public B { };   //可当作ForwordIterator
struct D2 : public D1 { };  //可当作BidirectionalIterator

template <class I>
func(I &p, B) {
    cout << "B version" << endl;
}

template <class I>
func(I &p, D2) {
    cout << "D2 version" << endl;
}

int main()
{
    int *p;
    func(p, B());      //输出"B version"
    func(p, D1());      //输出"B version"
    func(p, D2());      //输出"D2 version"
}
