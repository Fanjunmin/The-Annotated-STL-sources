//2.2.3 对象的构造和析构工具：construct(),destory()
//stl_construct.h

#include <new.h>    //placement new

template <typename T1, typename T2>
inline void construct(T1* p, const T2& value){
    new (p) T1(value); //将初值value设定到指针p所指空间
}

template <typename T>
inline void destory(T* pointer){
    pointer->~T();  //调用析构函数
}

//将迭代器[first, last)内所有对象析构掉
template <typename ForwardIterator>
inline void destory(ForwardIterator first, ForwardIterator last){
    __destory(first, last, value_type(first));  //value_type()获取对象型别
}

//判断元素是否有 trivial destructor
template <typename ForwardIterator, typename T>
inline void __destroy(ForwardIterator first, ForwardIterator last, T*){
    typedef typename __type_traits<T>::has_trivial_destructor trivial_destructor;
    __destory_aux(first, last, trivial_destructor());
}

//元素有 non-trivial destructor，依次调用析构函数
template <typename ForwardIterator>
inline void __destory_aux(ForwardIterator first, ForwardIterator last, __false_type){
    for( ; first < last; ++first){
        destory(&*first);
    }
}

//元素有 trivial destructor，什么也不做？
template <typename ForwardIterator>
inline void __destory_aux(ForwardIterator, ForwardIterator, __true_type){}

//特化版本:针对char*和wchar_t*
template<>
inline void destory(char*, char*) {}
inline void destory(wchar_t*, wchar_t*) {}
