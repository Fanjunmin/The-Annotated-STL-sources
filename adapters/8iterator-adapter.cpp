//filename : 8iterator-adapter.cpp

#include <iterator> //for iterator adapter
#include <deque>
#include <algorithm>    //for copy()
#include <iostream>
using namespace std;

int main()
{
    ostream_iterator<int> outite(cout, " ");
    int ia[] = {0,1,2,3,4,5};
    deque<int> id(ia, ia+6);
    copy(id.begin(), id.end(), outite); //0 1 2 3 4 5
    cout << endl;

    copy(ia+1, ia+2, front_inserter(id));
    copy(id.begin(), id.end(), outite); //1 0 1 2 3 4 5
    cout << endl;

    copy(ia+3, ia+4, back_inserter(id));
    copy(id.begin(), id.end(), outite); //1 0 1 2 3 4 5 3
    cout << endl;

    deque<int>::iterator ite = find(id.begin(), id.end(), 5);
    copy(ia, ia+3, inserter(id, ite));
    copy(id.begin(), id.end(), outite); //1 0 1 2 3 4 0 1 2 5 3
    cout << endl;

    copy(id.rbegin(), id.rend(), outite);   //3 5 2 1 0 4 3 2 1 0 1
    cout << endl;

    istream_iterator<int> inite(cin), eos;  //eos:end of stream
    copy(inite, eos, inserter(id, id.begin()));
    copy(id.begin(), id.end(), outite);
    return 0;
}
