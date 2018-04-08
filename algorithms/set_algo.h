#ifndef SET_ALGO_H_INCLUDED
#define SET_ALGO_H_INCLUDED
#include<algorithm>

template <class InputIterator1, class InputIterator2, class OutputIterator>
OutputIterator my_set_union(InputIterator1 first1, InputIterator1 last1,
                         InputIterator2 first2, InputIterator2 last2,
                         OutputIterator result) {
    //两端移动迭代器: 将较小者记录并且前进，另外的迭代器不动
    while(first1 != last1 && first2 != last2) {
        if(*first1 < *first2) {
            *result = *first1;
            ++first1;
        }
        else if(*first2 < *first1) {
            *result = *first2;
            ++first2;
        }
        else {  //*first1 == *first2
            *result = *first1;
            ++first1;
            ++first2;
        }
        ++result;
    }
    //将剩余的元素拷贝到目的端
    //[first1, last1) [first2, last2)至少有一个是空白的区间
    return copy(first2, last2, copy(first1, last1, result));
}

template <class InputIterator1, class InputIterator2, class OutputIterator, class Compare>
OutputIterator my_set_union(InputIterator1 first1, InputIterator1 last1,
                         InputIterator2 first2, InputIterator2 last2,
                         OutputIterator result, Compare comp) {
    //两端移动迭代器: 将较小者记录并且前进，另外的迭代器不动
    while(first1 != last1 && first2 != last2) {
        if(comp(*first1, *first2)) {
            *result = *first1;
            ++first1;
        }
        else if(comp(*first2, *first1)) {
            *result = *first2;
            ++first2;
        }
        else {  //*first1 == *first2
            *result = *first1;
            ++first1;
            ++first2;
        }
        ++result;
    }
    //将剩余的元素拷贝到目的端
    //[first1, last1) [first2, last2)至少有一个是空白的区间
    return copy(first2, last2, copy(first1, last1, result));
}

template <class InputIterator1, class InputIterator2, class OutputIterator>
OutputIterator my_set_intersection(InputIterator1 first1, InputIterator1 last1,
                         InputIterator2 first2, InputIterator2 last2,
                         OutputIterator result) {
    //两端移动迭代器
    while(first1 != last1 && first2 != last2) {
        if(*first1 < *first2) {
            ++first1;
        }
        else if(*first2 < *first1) {
            ++first2;
        }
        else {  //*first1 == *first2
            *result = *first1;
            ++first1;
            ++first2;
            ++result;
        }
    }
    return result;
}

template <class InputIterator1, class InputIterator2, class OutputIterator, class Compare>
OutputIterator my_set_intersection(InputIterator1 first1, InputIterator1 last1,
                         InputIterator2 first2, InputIterator2 last2,
                         OutputIterator result, Compare comp) {
    //两端移动迭代器
    while(first1 != last1 && first2 != last2) {
        if(comp(*first1, *first2)) {
            ++first1;
        }
        else if(comp(*first2, *first1)) {
            ++first2;
        }
        else {  //*first1 == *first2
            *result = *first1;
            ++first1;
            ++first2;
            ++result;
        }
    }
    return result;
}

template <class InputIterator1, class InputIterator2, class OutputIterator>
OutputIterator my_set_difference(InputIterator1 first1, InputIterator1 last1,
                         InputIterator2 first2, InputIterator2 last2,
                         OutputIterator result) {
    //两端移动迭代器: 将较小者记录并且前进，另外的迭代器不动
    while(first1 != last1 && first2 != last2) {
        if(*first1 < *first2) {
            *result = *first1;
            ++first1;
            ++result;
        }
        else if(*first2 < *first1) {
            ++first2;
        }
        else {  //*first1 == *first2
            ++first1;
            ++first2;
        }
    }
    return copy(first1, last1, result);
}

template <class InputIterator1, class InputIterator2, class OutputIterator, class Compare>
OutputIterator my_set_difference(InputIterator1 first1, InputIterator1 last1,
                         InputIterator2 first2, InputIterator2 last2,
                         OutputIterator result, Compare comp) {
    //两端移动迭代器: 将较小者记录并且前进，另外的迭代器不动
    while(first1 != last1 && first2 != last2) {
        if(comp(*first1, *first2)) {
            *result = *first1;
            ++first1;
            ++result;
        }
        else if(comp(*first2, *first1)) {
            ++first2;
        }
        else {  //*first1 == *first2
            ++first1;
            ++first2;
        }
    }
    return copy(first1, last1, result);
}

template <class InputIterator1, class InputIterator2, class OutputIterator>
OutputIterator my_set_symmetric_difference(InputIterator1 first1, InputIterator1 last1,
                         InputIterator2 first2, InputIterator2 last2,
                         OutputIterator result) {
    //两端移动迭代器: 将较小者记录并且前进，另外的迭代器不动
    while(first1 != last1 && first2 != last2) {
        if(*first1 < *first2) {
            *result = *first1;
            ++first1;
            ++result;
        }
        else if(*first2 < *first1) {
            *result = *first2;
            ++first2;
            ++result;
        }
        else {  //*first1 == *first2
            ++first1;
            ++first2;
        }
    }
    return copy(first2, last2, copy(first1, last1, result));
}

template <class InputIterator1, class InputIterator2, class OutputIterator, class Compare>
OutputIterator my_set_symmetric_difference(InputIterator1 first1, InputIterator1 last1,
                         InputIterator2 first2, InputIterator2 last2,
                         OutputIterator result, Compare comp) {
    //两端移动迭代器: 将较小者记录并且前进，另外的迭代器不动
    while(first1 != last1 && first2 != last2) {
        if(comp(*first1, *first2)) {
            *result = *first1;
            ++first1;
            ++result;
        }
        else if(comp(*first2, *first1)) {
            *result = *first2;
            ++first2;
            ++result;
        }
        else {  //*first1 == *first2
            ++first1;
            ++first2;
        }
    }
    return copy(first2, last2, copy(first1, last1, result));
}

#endif // SET_ALGO_H_INCLUDED
