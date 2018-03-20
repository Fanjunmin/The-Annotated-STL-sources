//3.2 链表的迭代器
//filename : 3mylist-iter.h

#ifndef MYLISTITER_H_INCLUDED
#define MYLISTITER_H_INCLUDED
#include "3mylist.h"

template <typename Item>
class ListIter{ //该迭代器只为链表服务
public:
    ListIter(Item* p = 0) : ptr(p) {}   //default ctor
    //copy ctor和operator=()编译器提供缺省行为足够
    Item& operator*() const { return *ptr; }
    Item* operator->() const { return ptr; }
    bool operator==(const ListIter& i) const { return ptr == i.ptr; }
    bool operator!=(const ListIter& i) const { return ptr != i.ptr; }
    //++运算符重载
    ListIter& operator++() {ptr = ptr->next; return *this;}  //前置++
    ListIter operator++(int){
        //后置++，额外形参，对象副本作为右值返回
        ListIter* tmp = this;
        ++*this;    //使用前置++
        return tmp;
    }
private:
    Item* ptr;  //保持与容器的联系,这个指针指向链表节点
};
#endif // MYLISTITER_H_INCLUDED
