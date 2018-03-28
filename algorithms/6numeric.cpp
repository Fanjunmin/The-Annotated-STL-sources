//filename : 6numeric.cpp

#include <numeric>
#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator> //for ostream_iterator
#include <functional>
using namespace std;

int main()
{
    int ia[5] = { 1, 2, 3, 4, 5 };
    vector<int> iv(begin(ia), end(ia));

    cout << accumulate(iv.begin(), iv.end(), 0) << endl;    //15 = 0+1+2+3+4+5
    cout << accumulate(iv.begin(), iv.end(), 0, minus<int>()) << endl;  //-15=0-1-2-3-4-5
    cout << inner_product(iv.begin(), iv.end(), iv.begin(), 10) << endl;   //65 = 10+1+4+9+16+25
    cout << inner_product(iv.begin(), iv.end(), iv.begin(), 10, minus<int>(), plus<int>()) << endl;//-20=10-1-2-4-6-8-10

    ostream_iterator<int> oite(cout, " ");
    partial_sum(iv.begin(), iv.end(), oite);
    cout << endl;
    partial_sum(iv.begin(), iv.end(), oite, minus<int>());
    cout << endl;
    return 0;
}
