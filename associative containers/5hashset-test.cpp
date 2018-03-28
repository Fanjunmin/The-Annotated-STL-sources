//filename : 5hashset-test.cpp
#include <iostream>
#include <hash_set>
#include <cstring>
using namespace std;

struct eqstr    //key_equal()
{
    bool operator()(const char* s1, const char* s2) const
    {
        return strcmp(s1, s2) == 0;
    }
};

//特别注意：hash_set在命名空间__gnu_cxx里
void lookup(const __gnu_cxx::hash_set<const char*, hash<const char*>, eqstr>& Set, const char* word)
{
    __gnu_cxx::hash_set<const char*, hash<const char*>, eqstr>::const_iterator it
        = Set.find(word);
    cout << word << ": "
         << (it != Set.end() ? "present" : "not present")
         << endl;
}

int main()
{
    //函数原型:hash_set(size_type n, const hasher& hf, const key_equal& eql);
    __gnu_cxx::hash_set<const char*, hash<const char*>, eqstr> Set;
    Set.insert("kiwi");
    Set.insert("plum");
    Set.insert("apple");
    Set.insert("mango");
    Set.insert("apricot");
    Set.insert("banana");

    lookup(Set, "mango");
    lookup(Set, "apple");
    lookup(Set, "durian");

    auto iter1 = Set.begin();
    auto iter2 = Set.end();
    for(; iter1 != iter2; ++iter1)
        cout << *iter1 << ' ';  //banana kiwi plum apple mango apricot
    cout << endl;

    __gnu_cxx::hash_set<int> iset;
    iset.insert(59);
    iset.insert(63);
    iset.insert(108);
    iset.insert(2);
    iset.insert(53);
    iset.insert(55);

    auto ite1 = iset.begin();
    auto ite2 = iset.end();
    for(; ite1 != ite2; ++ite1)
        cout << *ite1 << ' ';   // 2 53 55 59 63 108
    cout << endl;

    __gnu_cxx::hash_set<int> iset2; //Hashtable大小缺省指定为100，根据SGI涉及采用质数193
    iset2.insert(3);
    iset2.insert(196);
    iset2.insert(1);
    iset2.insert(389);
    iset2.insert(194);
    iset2.insert(387);
    //387=194=1 mod 193
    //389=196=3 mod 193

    auto ite21 = iset2.begin();
    auto ite22 = iset2.end();
    for(; ite21 != ite22; ++ite21)
        cout << *ite21 << ' ';   // 387 194 1 389 196 3
    cout << endl;
    return 0;
}
