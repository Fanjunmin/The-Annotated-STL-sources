//3.2 将list和find()用ListIter迭代器粘连起来
//filename : 3mylist-iter-test

#include "3mylist-iter.h"
#include <algorithm>
int main(){
    List<int> mylist;
    for(int i = 0; i < 5; ++i){
        mylist.insert_front(i);
        mylist.insert_end(i+2);
    }
    mylist.display(std::cout);
    ListIter<ListItem<int> > begin(mylist.front());
    ListIter<ListItem<int> > end;
    ListIter<ListItem<int> > iter;
    iter = std::find(begin, end, 3);
    if(iter == end)
        std::cout << "not found" << std::endl;
    else
        std::cout << "found : " << iter->value() << std::endl;
    iter = std::find(begin, end, 7);
    if(iter == end)
        std::cout << "not found" << std::endl;
    else
        std::cout << "found : " << iter->value() << std::endl;
    return 0;
}
