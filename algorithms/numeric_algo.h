//filename:numeric_algo.h
#ifndef NUMERIC_ALGO_H_INCLUDED
#define NUMERIC_ALGO_H_INCLUDED

//II:InputIterator  BO:BinaryOperator OI:OutputIterator
//FI:ForwardIterator

//accumulate
template<class II, class T>
T my_accumulate(II first, II last, T init) {
    for(; first != last; ++first)
        init += *first;     //累加
    return init;
}
template<class II, class T, class BO>
T my_accumulate(II first, II last, T init, BO binary_op) {
    for(; first != last; ++first)
        init = binary_op(init, *first);     //对每一个元素二元操作
    return init;
}

//adjacent_difference
template<class II, class OI>
OI my_adjacent_difference(II first, II last, OI result) {
    if(first == last)
        return result;
    *result = *first;
    auto value = *first;
    while(++first != last) {
        auto tmp = *first;
        *++result = tmp - value;
        value = tmp;
    }
    return result;
}
template<class II, class OI, class BO>
OI my_adjacent_difference(II first, II last, OI result, BO binary_op) {
    if(first == last)
        return result;
    *result = *first;
    auto value = *first;
    while(++first != last) {
        auto tmp = *first;
        *++result = binary_op(tmp, value);
        value = tmp;
    }
    return result;
}

//inner_product
template<class II1, class II2, class T>
T my_inner_product(II1 first1, II1 last1, II2 first2, T init) {
    for(; first1 != last1; ++first1, ++first2)
        init += (*first1 * *first2);
    return init;
}
template<class II1, class II2, class T, class BO1, class BO2>
T my_inner_product(II1 first1, II1 last1, II2 first2, T init, BO1 binary_op1, BO2 binary_op2) {
    for(; first1 != last1; ++first1, ++first2)
        init = binary_op1(init, binary_op2(*first1, *first2));
    return init;
}

//partial_sum
template<class II, class OI>
OI my_partial_sum(II first, II last, OI result) {
    if(last == first)
        return result;
    *result = *first;
    auto value = *first;
    while(++first != last) {
        value += *first;
        *++result = value;
    }
    return result;
}
template<class II, class OI, class BO>
OI my_partial_sum(II first, II last, OI result, BO binary_op) {
    if(last == first)
        return result;
    *result = *first;
    auto value = *first;
    while(++first != last) {
        value = binary_op(value, *first);
        *++result = value;
    }
    return result;
}

//power
template<typename T, class Integer>
T my_power(T x, Integer n) {
    if(n == 0)
        return 1;
    else {
        while((n & 1) == 0) {
            n >>= 1;
            x *= x;
        }
        T result = x;
        while(n >>= 1) {
            x *= x;
            if((n & 1) != 0)
                result *= x;
        }
        return result;
    }
}

//iota
template<class FI, class T>
void my_iota(FI first, FI last, T value) {
    while(first != last) *first++ = value++;
}
#endif // NUMERIC_ALGO_H_INCLUDED
