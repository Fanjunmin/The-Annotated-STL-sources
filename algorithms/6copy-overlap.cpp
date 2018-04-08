//filename:6copy-overlap.cpp
#include <iostream>
#include <algorithm>
#include <deque>
#define cel cout << endl;
using namespace std;

template<typename T>
struct display {
    void operator() (const T& x) const {
        cout << x << ' ';
    }
};

int main()
{
    {
        //输出区间起点与输入区间不重叠,复制完全没问题
        int ia[] = {0,1,2,3,4,5,6,7,8};
        copy(ia+2, ia+7, ia);
        for_each(ia, ia+9, display<int>()); //2 3 4 5 6 5 6 7 8
        cel;
    }

    {
        //输出区间起点与输入区间重叠,复制可能有问题
        int ia[] = {0,1,2,3,4,5,6,7,8};
        copy(ia+2, ia+7, ia+4);
        //这里没问题是因为copy算法调用的memmove(ia+4, ia+2, 5);
        for_each(ia, ia+9, display<int>());//0 1 2 3 2 3 4 5 6 7
        cel;
    }

    {
        int ia[] = {0,1,2,3,4,5,6,7,8};
        deque<int> id(ia, ia+9);
        auto first = id.begin(), last = id.end();
        ++++first;      //advance(first, 2)
        cout << *first << endl; //2
        ----last;       //advance(last, -2)
        cout << *last << endl;  //7
        auto result = id.begin();
        cout << *result << endl;  //0
        //输出区间起点与输入区间不重叠,复制完全没问题
        copy(first, last, result);
        for_each(id.begin(), id.end(), display<int>()); //2 3 4 5 6 5 6 7 8
        cel;
    }

    {
        int ia[] = {0,1,2,3,4,5,6,7,8};
        deque<int> id(ia, ia+9);
        auto first = id.begin(), last = id.end();
        ++++first;      //advance(first, 2)
        cout << *first << endl; //2
        ----last;       //advance(last, -2)
        cout << *last << endl;  //7
        auto result = id.begin();
        advance(result, 4);
        cout << *result << endl;  //4
        //输出区间起点与输入区间重叠,复制可能有问题
        copy(first, last, result);
        //复制结果并不如我们预料是因为copy算法并没有调用memmove(),但是为何结果又是正确的
        for_each(id.begin(), id.end(), display<int>()); //0 1 2 3 2 3 4 5 6
        //按__copy_d()结果应该是:0 1 2 3 2 3 2 3 2    (在VS中确实是这样的)
        cel;
    }
    return 0;
}
