//filename: 6copy-test.cpp

#include <iostream>
#include <algorithm>
#include <deque>
#include <vector>
#include <list>
#include <string>

#define cel cout << endl;

using namespace std;

class C
{
public:
    C() : _data(3) {}
    //there is a trivial assignment operator
private:
    int _data;
};

int main()
{
    //测试1
    const char ccs[5] = {'a', 'b', 'c', 'd', 'e'};
    char ccd[5];
    copy(ccs, ccs+5, ccd);  //调用的版本是copy(const char*)

    //测试2
    const wchar_t cwcs[5] = {'a', 'b', 'c', 'd', 'e'};
    wchar_t cwcd[5];
    copy(ccs, ccs+5, ccd);  //调用的版本是copy(const wchar_t*)

    //测试3
    int ia[5] = {0,1,2,3,4};
    copy(ia, ia+5, ia);
    //调用的版本是copy() => __copy_dispatch() => __copy_t(__true_type)

    //测试4
    //list 迭代器被视为InputIterator
    list<int> ilists(ia, ia+5);
    list<int> ilistd(5);
    copy(ilists.begin(), ilists.end(), ilistd.begin());
    //调用的版本是copy() => __copy_dispatch() => __copy(input_iterator)

    //测试5
    //vector 迭代器被视为原生指针
    vector<int> ivecs(ia, ia+5);    //这个构造函数最底层调用的还是copy()
    vector<int> ivecd(5);
    copy(ivecs.begin(), ivecs.end(), ivecd.begin());
    //调用的版本是copy() => __copy_dispatch() => __copy_t(__true_type)

    //测试6
    //class C 具有trivial operator=，但是编译器无法验证"用户自己定义型别"
    //编译器仅有能力验证"c++标量型别(scalar type)"
    C c[5];
    vector<C> Cvs(c, c+5);
    vector<C> Cvd(5);
    copy(Cvs.begin(), Cvs.end(), Cvd.begin());
    //调用的版本是copy() => __copy_dispatch() => __copy_t(__false_type)

    //测试7
    //deque 迭代器被归类为random_access_iterator
    deque<C> Cds(c, c+5);
    deque<C> Cdd(5);
    copy(Cds.begin(), Cds.end(), Cdd.begin());
    //调用的版本是copy() => __copy_dispatch() => __copy(random_access_iterator) => __copy_d()

    //测试8
    vector<string> strvs{"jjhou", "grace", "david", "jason", "jerry"};
    vector<string> strvd(5);
    copy(strvs.begin(), strvs.end(), strvd.begin());
    //调用的版本是copy() => __copy_dispatch(T*, T*) => __copy_t(__false_type) => __copy_d()

    //测试9
    deque<string> strds(5), strdd(5);
    strds.push_back("jjhou");
    strds.push_back("grace");
    strds.push_back("david");
    strds.push_back("jason");
    strds.push_back("jerry");
    copy(strds.begin(), strds.end(), strdd.begin());
    //调用的版本是copy() => __copy_dispatch() => __copy(random_access_iterator) =>__copy_d()
    return 0;
}
