//filename:8functor=adapter.cpp
#include <algorithm>
#include <functional>
#include <vector>
#include <iostream>
#include <iterator>
using namespace std;

void print(int i) {
    cout << i << " ";
}

class Int
{
public:
    explicit Int(int i) : m_i(i) { }
    void print1() const { cout << '[' << m_i << ']';}
private:
    int m_i;
};

int main()
{
    ostream_iterator<int> outite(cout, " ");
    int ia[6] = {2, 21, 12, 7, 19, 23};
    vector<int> iv(ia, ia+6);

    //找到大于12元素个数
    cout << count_if(iv.begin(), iv.end(), not1(bind2nd(less<int>(), 12))) << endl;
    cout << count_if(iv.begin(), iv.end(), [](int x) { return x >= 12;}) << endl;   //lambda表达式

    //transform(iv.begin(), iv.end(), outite, compose1(bind2nd(multiplies<int>(), 3), bind2nd(plus<int>(), 2) ));
    transform(iv.begin(), iv.end(), outite, [](int x){ return 3*(x+2); });  //12 69 42 27 63 75
    cout << endl;

    copy(iv.begin(), iv.end(), outite); //2, 21, 12, 7, 19, 23
    cout << endl;

    for_each(iv.begin(), iv.end(), print); //2, 21, 12, 7, 19, 23
    cout << endl;

    for_each(iv.begin(), iv.end(), ptr_fun(print)); //2, 21, 12, 7, 19, 23
    cout << endl;

    Int t1(3), t2(7), t3(20), t4(14), t5(68);
    vector<Int> Iv;
    Iv.push_back(t1);
    Iv.push_back(t2);
    Iv.push_back(t3);
    Iv.push_back(t4);
    Iv.push_back(t5);
    for_each(Iv.begin(), Iv.end(), mem_fun_ref(&Int::print1));  //[3][7][20][14][68]
    return 0;
}
