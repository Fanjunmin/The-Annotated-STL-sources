//filename:7functor-logical.cpp
#include<iostream>
#include<functional>

using namespace std;

int main()
{
    logical_and<int> and_obj;
    logical_not<int> not_obj;
    logical_or<int> or_obj;

    cout << and_obj(0, 1) << endl;      //0
    cout << not_obj(1) << endl;         //0
    cout << or_obj(1, 0) << endl;       //1

    cout << logical_and<int>()(0, 1) << endl;   //0
    cout << logical_not<int>()(1) << endl;      //0
    cout << logical_or<int>()(1, 0) << endl;    //1

    return 0;
}
