//filename:7functor-rational.cpp
//关系运算类仿函数

#include <functional>
#include <iostream>
using namespace std;

int main()
{
    equal_to<int> equal_to_obj;
    not_equal_to<int> not_equal_to_obj;
    greater<int> greater_obj;
    less<int> less_obj;
    greater_equal<int> greater_equal_obj;
    less_equal<int> less_equal_obj;

    cout << equal_to_obj(3, 5) << endl;         //0
    cout << not_equal_to_obj(3, 5) << endl;     //1
    cout << greater_obj(3, 5) << endl;          //0
    cout << less_obj(3, 5) << endl;             //1
    cout << greater_equal_obj(3, 5) << endl;    //0
    cout << less_equal_obj(3, 5) << endl;       //1

    cout << equal_to<int>()(3, 5) << endl;      //0
    cout << not_equal_to<int>()(3, 5) << endl   //1
    cout << greater<int>()(3, 5) << endl;       //0
    cout << less<int>()(3, 5) << endl;          //1
    cout << greater_equal<int>()(3, 5) << endl; //0
    cout << less_equal<int>()(3, 5) << endl;    //1
    return 0;
}
