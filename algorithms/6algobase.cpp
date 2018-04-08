//filename:6algobase.cpp

#include <algorithm>
#include <vector>
#include <functional>
#include <iostream>
#include <iterator>
#include <string>
#include "base_algo.h"
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
    int ia[9] = {0,1,2,3,4,5,6,7,8};
    vector<int> iv1(ia, ia+5);
    vector<int> iv2(ia, ia+9);
    cout << *(mismatch(iv1.begin(), iv1.end(), iv2.begin()).first); cel;//未知值， equals *iv1.end();
    cout << *(my_mismatch(iv1.begin(), iv1.end(), iv2.begin()).first); cel;
    cel;
    cout << *(mismatch(iv1.begin(), iv1.end(), iv2.begin()).second);  cel;
    cout << *(my_mismatch(iv1.begin(), iv1.end(), iv2.begin()).second);  cel;  //5
    cel;
    cout << equal(iv1.begin(), iv1.end(), iv2.begin());  cel;//1 true
    cout << my_equal(iv1.begin(), iv1.end(), iv2.begin());  cel;
    cel;
    cout << equal(iv1.begin(), iv1.end(), &ia[3]);  cel; //0 false {0,1,2,3,4} 不等于 {3,4,5,6,7}
    cout << my_equal(iv1.begin(), iv1.end(), &ia[3]);  cel;
    cel;
    cout << equal(iv1.begin(), iv1.end(), &ia[3], less<int>());  cel;//1 true  {0,1,2,3,4} 小于 {3,4,5,6,7}
    cout << my_equal(iv1.begin(), iv1.end(), &ia[3], less<int>());  cel;
    cel;
    fill(iv1.begin(), iv1.end(), 9); cel;
    for_each(iv1.begin(), iv1.end(), display<int>());  cel; //9 9 9 9 9
    cel;
    fill_n(iv1.begin(), 3, 7);
    for_each(iv1.begin(), iv1.end(), display<int>()); cel;  //7 7 7 9 9
    cel;
    auto ite1 = iv1.begin();
    auto ite2 = ite1;
    advance(ite2, 3);
    iter_swap(ite1, ite2);
    cout << *ite1 << ' ' << *ite2 << endl;
    for_each(iv1.begin(), iv1.end(), display<int>()); cel;  //9 7 7 7 9
    cel;
    cout << max(*ite1, *ite2) << endl;  //9
    cout << min(*ite1, *ite2) << endl;  //7
    //下列直接比较迭代器的大小没有意义
    cout << *max(ite1, ite2) << endl;   //7
    cout << *min(ite1, ite2) << endl;   //9
    swap(*iv1.begin(), *iv2.begin());
    for_each(iv1.begin(), iv1.end(), display<int>());  cel; //0 7 7 7 9
    for_each(iv2.begin(), iv2.end(), display<int>());   cel;//9 1 2 3 4 5 6 7 8
    string stra1[] = {"Jamie", "JJHou", "Jason"};
    string stra2[] = {"Jamie", "JJhou", "Jerry"};
    cout << lexicographical_compare(stra1, stra2+2, stra2, stra2+2) << endl;    //1 JJHou < JJhou
    cout << lexicographical_compare(stra1, stra1+2,stra2, stra2+2, greater<string>()) << endl;  //0 great<string>("JJHou", "JJhou) is false
    return 0;
}
