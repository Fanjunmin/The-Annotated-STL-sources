//filename : 6numeric.cpp

#include <numeric>
#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator> //for ostream_iterator
#include <functional>
#include "numeric_algo.h"
#define cel cout << endl
using namespace std;

int main()
{
    int ia[5] = { 1, 2, 3, 4, 5 };
    vector<int> iv(begin(ia), end(ia));

    cout << accumulate(iv.begin(), iv.end(), 0) << endl;    //15 = 0+1+2+3+4+5
    cout << my_accumulate(iv.begin(), iv.end(), 0) << endl;   cel;
    cout << accumulate(iv.begin(), iv.end(), 0, minus<int>()) << endl;  //-15=0-1-2-3-4-5
    cout << my_accumulate(iv.begin(), iv.end(), 0, minus<int>()) << endl;   cel;
    cout << inner_product(iv.begin(), iv.end(), iv.begin(), 10) << endl;   //65 = 10+1+4+9+16+25
    cout << my_inner_product(iv.begin(), iv.end(), iv.begin(), 10) << endl;    cel;
    cout << inner_product(iv.begin(), iv.end(), iv.begin(), 10, minus<int>(), plus<int>()) << endl;//-20=10-1-2-4-6-8-10
    cout << my_inner_product(iv.begin(), iv.end(), iv.begin(), 10, minus<int>(), plus<int>()) << endl; cel;

    ostream_iterator<int> oite(cout, " ");
    partial_sum(iv.begin(), iv.end(), oite);    //1,3,6,10,15
    cel;
    my_partial_sum(iv.begin(), iv.end(), oite);
    cel;    cel;
    partial_sum(iv.begin(), iv.end(), oite, minus<int>());  //1,-1,-4,-8,-13
    cel;
    my_partial_sum(iv.begin(), iv.end(), oite, minus<int>());
    cel;    cel;
    adjacent_difference(iv.begin(), iv.end(), oite); //1,1,1,1,1
    cel;
    my_adjacent_difference(iv.begin(), iv.end(), oite);
    cel;    cel;
    cout << pow(10, 3) << endl; //1000
    cout << my_power(10, 3) << endl;
    //power() SGI STL专属,不在标准之列
    //cout << power(10, 3) << endl;   //10*10*10
    //cout << power(10, 3, plus<int>()) << endl;  //10+10+10
    int n = 3;
    iota(iv.begin(), iv.end(), n);
    for(auto i : iv)
        cout << i << ends;
    return 0;
}
