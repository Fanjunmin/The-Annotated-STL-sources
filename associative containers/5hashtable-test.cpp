//filename 5hashtable-test.cpp

#include <hash_set>
#include <iostream>
using namespace std;

int main()
{
    __gnu_cxx::hashtable<int, int, hash<int>, identity<int>, equal<int>>
        iht(50, hash<int>(), equal_to<int>());
    return 0;
}
