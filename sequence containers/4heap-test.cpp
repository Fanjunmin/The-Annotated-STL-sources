//4.7.4 heap²âÊÔ
//filename 4heap-test.cpp
#include <vector>
#include <iostream>
#include <algorithm>    //heap algorithms
using namespace std;

int main()
{
    {
    //heapµ×²ãÒÔvector
    int ia[9] = {0, 1, 2, 3, 4, 8, 9, 3, 5};
    vector<int> ivec(ia, ia+9);
    make_heap(ivec.begin(), ivec.end());
    for(auto x : ivec)
        cout << x << ' ';   //9 5 8 3 4 0 2 3 1
    cout <<endl;

    ivec.push_back(7);
    push_heap(ivec.begin(), ivec.end());
    for(auto x : ivec)
        cout << x << ' ';   //9 7 8 3 5 0 2 3 1 4
    cout <<endl;

    pop_heap(ivec.begin(), ivec.end());
    cout << ivec.back() << endl;    //9
    ivec.pop_back();

    for(auto x : ivec)
        cout << x << ' ';   //8 7 4 3 5 0 2 3 1
    cout <<endl;

    sort_heap(ivec.begin(), ivec.end());
    for(auto x : ivec)
        cout << x << ' ';   //0 1 2 3 4 5 7 8
    cout <<endl;
    }

    {
    int ia[9] = {0, 1, 2, 3, 4, 8, 9, 3, 5};
    make_heap(ia, ia+9);

    sort_heap(ia, ia+9);
    for(auto x : ia)
        cout << x << ' ';   //0 1 2 3 3 4 5 8 9
    cout <<endl;

    make_heap(ia, ia+9);    //9 8 5 3 3 4 2 1 0
    pop_heap(ia, ia+9);
    cout << ia[8] << endl;  //9
    for(auto x : ia)
        cout << x << ' ';   //8 3 5 3 0 4 2 1
    cout <<endl;
    }

    {
    int ia[6] = {4, 1, 7, 6, 2, 5};
    make_heap(ia, ia+6);
    for(auto x : ia)
        cout << x << ' ';   //7 6 5 1 2 4
    cout <<endl;
    }
}
