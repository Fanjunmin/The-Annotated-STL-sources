#ifndef BASE_ALGO_H_INCLUDED
#define BASE_ALGO_H_INCLUDED
#include <stddef.h>
#include <cstring>
#include <utility>
//II:InputIterator  BO:BinaryOperator OI:OutputIterator
//FI:ForwardIterator CMP:compare

//equal
template <class II1, class II2>
inline bool my_equal(II1 first1, II1 last1, II2 first2) {
    for(; first1 != last1; ++first1, ++first2) {
        if(*first1 != *first2)
            return false;
    }
    return true;
}
template <class II1, class II2, class CMP>
inline bool my_equal(II1 first1, II1 last1, II2 first2, CMP comp) {
    for(; first1 != last1; ++first1, ++first2) {
        if(!comp(*first1, *first2))
            return false;
    }
    return true;
}

//fill
template<class FI, class T>
void my_fill(FI first, FI last, const T& value) {
    for(; first != last; ++first)
        *first = value;
}

//fill_n
template<class OI, class T>
OI my_fill(OI first, size_t n, const T& value) {
    for(; n > 0; --n)
        *first++ = value;
    return first;
}

//iter_swap
template<class FI1, class FI2>
inline void my_iter_swap(FI1 a, FI2 b) {
    auto tmp = *a;
    *a = *b;
    *b = tmp;
}

//lexicographical_compare
template<class II1, class II2>
bool my_lexicographical_compare(II1 first1, II1 last1, II2 first2, II2 last2) {
    for(; first1 != last1 && first2 != last2; ++first1, ++first2) {
        if(*first1 < *first2)
            return true;
        else if(*first2 < *first1)
            return false;
    }
    return first1 == last1 && first2 != last2;
}
template<class II1, class II2, class CMP>
bool my_lexicographical_compare(II1 first1, II1 last1, II2 first2, II2 last2, CMP comp) {
    for(; first1 != last1 && first2 != last2; ++first1, ++first2) {
        if(comp(*first1, *first2))
            return true;
        else if(comp(*first2, *first1))
            return false;
    }
    return first1 == last1 && first2 != last2;
}
//lexicographical_compare 的const char* 和const unsigned char*特化版本
bool my_lexicographical_compare(const char* first1, const char* last1,
                                const char* first2, const char* last2) {
    const size_t len1 = last1 - first1;
    const size_t len2 = last2 - first2;
    const int result = memcmp(first1, first2, std::min(len1, len2));
    return result != 0 ? result < 0 : len1 < len2;
}

bool my_lexicographical_compare(const unsigned char* first1, const unsigned char* last1,
                                const unsigned char* first2, const unsigned char* last2) {
    const size_t len1 = last1 - first1;
    const size_t len2 = last2 - first2;
    const int result = memcmp(first1, first2, std::min(len1, len2));
    return result != 0 ? result < 0 : len1 < len2;
}

//max
template <class T>
inline const T& my_max(const T& a, const T& b) {
    return a < b ? b : a;
}
template <class T, class CMP>
inline const T& my_max(const T& a, const T& b, CMP comp) {
    return comp(a, b) ? b : a;
}

//min
template <class T>
inline const T& my_min(const T& a, const T& b) {
    return b < a ? b : a;
}
template <class T, class CMP>
inline const T& my_min(const T& a, const T& b, CMP comp) {
    return comp(b, a) ? b : a;
}

//mismatch
template<class II1, class II2>
std::pair<II1, II2> my_mismatch(II1 first1, II1 last1, II2 first2) {
    while(first1 != last1 && *first1 == *first2){
        ++first1;
        ++first2;
    }
    return std::pair<II1, II2>(first1, first2);
}
template<class II1, class II2, class BO>
std::pair<II1, II2> my_mismatch(II1 first1, II1 last1, II2 first2, BO binary_op) {
    while(first1 != last1 && binary_op(*first1, *first2)){
        ++first1;
        ++first2;
    }
    return std::pair<II1, II2>(first1, first2);
}

//swap
template<class T>
inline void my_swap(T& a, T& b) {
    T tmp = a;
    a = b;
    b = tmp;
}

#endif // BASE_ALGO_H_INCLUDED
