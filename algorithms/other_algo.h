#ifndef OTHER_ALGO_H_INCLUDED
#define OTHER_ALGO_H_INCLUDED
#include <stddef.h>
#include <cstring>
#include <utility>
#include <type_traits>
//II:InputIterator  BO:BinaryOperator OI:OutputIterator
//FI:ForwardIterator CMP:compare BP:binaryPredict PD: predicate

//adjacent_find
template<class FI>
FI my_adjacent_find(FI first, FI last) {
    if(first == last)
        return first;
    FI next = first;
    while(++next != last){
        if(*next == *first) return first;
        first = next;
    }
    return last;
}
template<class FI>
FI my_adjacent_find(FI first, FI last, BP binary_pred) {
    if(first == last)
        return first;
    FI next = first;
    while(++next != last){
        if(binary_pred(*next, *first)) return first;
        first = next;
    }
    return last;
}

//count
template<class II, class T>
size_t my_count(II first, II last, const T& value) {
    size_t n = 0;
    for(; first != last; ++first) {
        if(*first == value) ++n;
    }
    return n;
}
template<class II, class T, class Size>
void my_count(II first, II last, const T& value, Size& n) {
    for(; first != last; ++first) {
        if(*first == value) ++n;
    }
}

//count_if
template<class II, class PD>
size_t my_count_if(II first, II last, PD pred) {
    size_t n = 0;
    for(; first != last; ++first) {
        if(pred(*first)) ++n;
    }
    return n;
}
template<class II, class PD, class Size>
void my_count_if(II first, II last, PD pred, Size& n) {
    for(; first != last; ++first) {
        if(pred(*first)) ++n;
    }
}

//find
template<class II, class T>
II my_find(II first, II last, const T& value) {
    while(first != last && *first != value)
        ++first;
    return first;
}

//find_if
template<class II, class PD>
II my_find_if(II first, II last, PD predicate) {
    while(first != last && !predicate(*first))
        ++first;
    return first;
}

//find_end
template<class FI1, class FI2>
inline FI1 my_find_end(FI1 first1, FI1 last1, FI2 first2, FI2 last2) {
    //有两个版本，分别是前向迭代器以及双向迭代器版本
    //通过iterator_category 传递不同的迭代器使用不同的重载函数
    //FI 版本
    if(first2 == last2)
        return last1;
    else {
        FI1 result = last1;
        while(1) {
            FI1 new_result = search(first1, last1, first2, last2);
            if(new_result == last1)
                return new_result;
            else {
                result = new_result;
                first1 = new_result;
                ++first1;
            }
        }
    }
}

//find_first_of
template<class II, class FI>
II my_find_first_of(II first1, II last1, FI first2, FI last2) {
    for(; first1 != last1; ++first1) {
        for(auto iter = first2; iter != last2; ++ iter) {
            if(*first1 == *iter)
                return first1;
        }
    }
    return last1;
}

template<class II, class FI, class BP>
II my_find_first_of(II first1, II last1, FI first2, FI last2, BP comp) {
    for(; first1 != last1; ++first1) {
        for(auto iter = first2; iter != last2; ++ iter) {
            if(comp(*first1, *iter))
                return first1;
        }
    }
    return last1;
}

//for_each
template<class II, class Function>
Function my_for_each(II first, II last, Function f) {
    for(; first != last; ++first) {
        f(*first);  //调用f,返回值被忽略
    }
    return f;
}

//generate
template<class II, class Generator>
void my_generate(II first, II last, Generator gen) {
    for(; first != last; ++first)
        *first = gen();
}

//generate_n
template<class OI, class Size, class Generator>
OI my_generate_n(OI first, Size n, Generator gen) {
    for(; n > 0; --n, ++first)
        *first = gen();
    return first;
}

//includes
template<class II1, class II2>
bool my_includes(II1 first1, II1 last1, II2 first2, II2 last2) {
    //默认[first2, last2)递增
    while(first1 != last1 && first2 != last2) {
        if(*first2 < *first1)
            return false;
        else if(*first1 < *first2)
            ++first1;
        else
            ++first1, ++first2;
    }
    return first2 == last2;
}
template<class II1, class II2, class CMP>
bool my_includes(II1 first1, II1 last1, II2 first2, II2 last2, CMP comp) {
    while(first1 != last1 && first2 != last2) {
        if(comp(*first2, *first1))
            return false;
        else if(comp(*first1, *first2))
            ++first1;
        else
            ++first1, ++first2;
    }
    return first2 == last2;
}

//max_element
template<class FI>
FI my_max_element(FI first, FI last) {
    if(first == last) return first;
    FI result = first;
    while(++first != last) {
        if(*result < *first) result = first;
    }
    return result;
}
template<class FI, class CMP>
FI my_max_element(FI first, FI last, CMP comp) {
    if(first == last) return first;
    FI result = first;
    while(++first != last) {
        if(comp(*result, *first) result = first;
    }
    return result;
}

//min_element
template<class FI>
FI my_min_element(FI first, FI last) {
    if(first == last) return first;
    FI result = first;
    while(++first != last) {
        if(*first < *result) result = first;
    }
    return result;
}
template<class FI, class CMP>
FI my_min_element(FI first, FI last, CMP comp) {
    if(first == last) return first;
    FI result = first;
    while(++first != last) {
        if(comp(*first, *result) result = first;
    }
    return result;
}

//merge(应用于有序区间)
template<class II1, class II2, class OI>
OI my_merge(II1 first1, II1 last1, II2 first2, II2 last2, OI result) {
    while(first1 != last1 && first2 != last2){
        if(*first2 < *first1){
            *result = *first2;
            ++first2;
        }
        else {
            *result = *first1;
            ++first1;
        }
        ++result;
    }
    //[first1, last1)[first2, last2)中必然有一个序列为空
    return copy(first1, last1, copy(first2, last2, result));
}
template<class II1, class II2, class OI, class CMP>
OI my_merge(II1 first1, II1 last1, II2 first2, II2 last2, OI result, CMP comp) {
    while(first1 != last1 && first2 != last2){
        if(comp(*first2, *first1)){
            *result = *first2;
            ++first2;
        }
        else {
            *result = *first1;
            ++first1;
        }
        ++result;
    }
    //[first1, last1)[first2, last2)中必然有一个序列为空
    return copy(first1, last1, copy(first2, last2, result));
}

//partition
template<class BI, class PD>
BI my_partition(BI first, BI last, PD pred) {
    while(true) {
        while(true) {
            if(first == last)
                return first;
            else if(pred(*first))
                ++first;
            else
                break;
        }
        --last;
        while(true) {
            if(first == last)
                return first;
            else if(!pred(*last))
                --last;
            else
                break;
        }
        iter_swap(first, last); //头尾指针交换
        ++first;
    }
}

//remove移除但非删除
template<class FI, class T>
FI my_remove(FI first, FI last, const T& value) {
    first = my_find(first, last, value);
    FI next = first;
    return first == last ? first : my_remove_copy(++next, last, first, value);
}

//remove_copy
template<class II, class OI, class T>
OI my_remove_copy(II first, II last, OI result, const T& value) {
    for(; first != last; ++first) {
        if(*first != value) {
            *result = *first;
            ++first;
        }
    }
    return result;
}

//remove_if
template<class FI, class PD>
FI my_remove_if(FI first, FI last, PD pred) {
    first = my_find_if(first, last, pred);
    FI next = first;
    return first == last ? first : my_remove_copy_if(++next, last, first, pred);
}

//remove_copy_if
template<class II, class OI, class PD>
OI my_remove_copy_if(II first, II last, OI result, PD pred) {
    for(; first != last; ++first) {
        if(!pred(*first)){
            *result = *first;
            ++result;
        }
    }
    return result;
}

//replace

//replace_copy

//replace_if

//replace_copy_if

//reverse

//reverse_copy

//rotate

//rotate_copy

//search

//search_n

//swap_ranges

//transform

//unique

//unique_copy

//lower_bound
//底层调用__lower_bound 根据迭代器的类型进行
template<class FI, class T>
inline FI my_lower_bound(FI first, FI last, const T& value) {
    //考虑随机访问迭代器
    auto len = last - first;
    decltype(len) half;
    decltype(first) middle;
    while (len > 0) {
        half = len >> 1;
        middle = first + half;
        if(*middle < value) {
            first = middle + 1;
            len = len - half - 1;
        }
        else
            len = half;
    }
    return first;
}
//upper_bound

//binary_search
template<class FI, class T>
bool my_binary_search(FI first, FI last, const T& value) {
    FI i = my_lower_bound(first, last, value);
    return i != last && !(value < *i);
}

template<class FI, class T, class CMP>
bool my_binary_search(FI first, FI last, const T& value, CMP comp) {
    FI i = my_lower_bound(first, last, value, comp);
    return i != last && !(value < *i);
}

//next_permutation

//prev_permutation

//random_shuffle

//partial_sort

//partial_sort_copy

//sort

//equal_range

//inplace_merge

//nth_element

//merge_sort

#endif // OTHER_ALGO_H_INCLUDED
