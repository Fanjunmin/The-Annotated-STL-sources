//filename : 6copy-backward-overlap.cpp
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
        copy_backward(ia+2, ia+7, ia+9);
        for_each(ia, ia+9, display<int>()); //0 1 2 3 2 3 4 5 6
        cel;
    }

    {
        //输出区间起点与输入区间重叠,复制可能有问题
        int ia[] = {0,1,2,3,4,5,6,7,8};
        copy_backward(ia+2, ia+7, ia+5);
        //这里没问题是因为copy_backward算法调用的memmove(ia, ia+2, 5);
        for_each(ia, ia+9, display<int>());//2 3 4 5 6 5 6 7 8
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
        auto result = id.end();
        //输出区间起点与输入区间不重叠,复制完全没问题
        copy_backward(first, last, result);
        for_each(id.begin(), id.end(), display<int>()); //0 1 2 3 2 3 4 5 6
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
        advance(result, 5);
        cout << *result << endl;  //5
        //输出区间起点与输入区间重叠,复制可能有问题
        copy_backward(first, last, result);
        //复制结果并不如我们预料是因为copy算法并没有调用memmove()
        for_each(id.begin(), id.end(), display<int>()); //2 3 4 5 6 5 6 7 8
        //按__copy_backward_d()结果应该是:6 5 6 5 6 5 6 7 8
        cel;
    }
    return 0;
}
