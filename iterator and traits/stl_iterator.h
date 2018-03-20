//3.4.5迭代器的型别：iterator_category
//通过iterator_traits萃取迭代器的类型以完成函数重载的目的
//filename:stl_iterator
#ifndef STL_ITERATOR_H_INCLUDED
#define STL_ITERATOR_H_INCLUDED

//5种迭代器类型
struct input_iterator_tag { };  //输入迭代器
struct output_iterator_tag { }; //输出迭代器
struct forward_iterator_tag : public input_iterator_tag { };    //前向迭代器
struct bidirectional_iterator_tag : public forward_iterator_tag { };    //双向迭代器
struct random_access_iterator_tag : public bidirectional_iterator_tag { };  //随机访问迭代器

//自行开发的迭代器必须有相应的五种内嵌类别，所以最好继承自以下class
template <class Category, class T, class Distance = ptr_diff_t
            class Point = T*, class Reference = T&>
struct iterator {
    typedef Category    iterator_category;
    typedef T           value_type;
    typedef Distance    difference_type;
    typedef Point       pointer;
    typedef Reference   reference;
};

//萃取机traints
template <class Iterator>
struct iterator_traits {
    typedef typename Iterator::iterator_category iterator_category;
    typedef typename Iterator::value_type        value_type;
    typedef typename Iterator::difference_type   difference_type;
    typedef typename Iterator::pointer           pointer;
    typedef typename Iterator::reference         reference;
};

//为原生指针的偏特化版本
template <class T>
struct iterator_traits <T*> {
    typedef random_access_iterator_tag  iterator_category;
    typedef T                           value_type;
    typedef ptrdiff_t                   difference_type;
    typedef T*                          pointer;
    typedef T&                          reference;
};

//为原生const指针的偏特化版本
template <class T>
struct iterator_traits <const T*> {
    typedef random_access_iterator_tag  iterator_category;
    typedef T                           value_type;
    typedef ptrdiff_t                   difference_type;
    typedef const T*                    pointer;
    typedef const T&                    reference;
};

//该函数决定迭代器的类型iterator_category
template <class Iterator>
inline typename iterator_traits<Iterator>::iterator_category
iterator_category (const Iterator&) {
    typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
    return category();  //这是返回的临时变量
}

//该函数决定迭代器的value_type,为何返回指针类型？
template <class Iterator>
inline typename iterator_traits<Iterator>::value_type*
value_type (const Iterator&) {
    return static_cast<iterator_traits<iterator>::value_type*>(0);
}

//该函数决定迭代器的difference_type,为何返回指针类型？
template <class Iterator>
inline typename iterator_traits<Iterator>::difference_type*
distance_type (const Iterator) {
    return static_assert<typename iterator_traits<Iterator>::difference_type*>(0);
}

//advanced(i, n)函数：将i累进n次
template <class InputIterator, class Distance>
inline void advanced (inputIterator &i, Distance n) {
    __advanced (i, n, iterator_category(i));
}

//针对输入迭代器
template <class InputIterator, class Distance>
inline void __advanced (InputIterator &i, Distance n, input_iterator_tag) {
    while (n--) ++i;
}

//针对前向迭代器，调用输入迭代器的版本
template <class ForwardIterator, class Distance>
inline void __advanced (ForwardIterator &i, Distance n, forward_iterator_tag) {
    __advanced(i, n, input_iterator_tag);
}

//针对双向迭代器
template <class BidirectionalIterator, class Distance>
inline void __advanced (BidirectionalIterator &i, Distance n, bidirectional_iterator_tag) {
    if (n >= 0)
        while (n--) ++i;
    else
        while (n++) --i;
}

//针对随机访问迭代器
template <class RandomAccessIterator, class Distance>
inline void __advanced (RandomAccessIterator &i, Distance n, random_access_iterator_tag) {
    i += n;
}

//distance(first, last)计算迭代器间的距离
template <class InputIterator>
inline typename iterator_traits<InputIterator>::difference_type
distance (InputIterator first, InputIterator last) {
    typedef typename iterator_traits<InputIterator>::iterator_category category;
    return __distance (first, last, category());
}

//针对InputIterator
template <class InputIterator>
inline typename iterator_traits<InputIterator>::difference_type
__distance (InputIterator first, InputIterator last, input_iterator_tag) {
    typename iterator_traits<InputIterator>::difference_type n = 0;
    while (first != last) {
        ++first;
        ++n;
    }
    return n;
}

//针对RandomAccessIterator
template <class RandomAccessIterator>
inline typename iterator_traits<RandomAccessIterator>::difference_type
__distance (RandomAccessIterator first, RandomAccessIterator last, random_access_iterator_tag) {
    typename iterator_traits<RandomAccessIterator>::difference_type n = last - first;
    return n;
}


#endif // STL_ITERATOR_H_INCLUDED
