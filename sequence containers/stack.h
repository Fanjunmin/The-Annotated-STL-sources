//filename stack.h
#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

template <class T, class Sequence = deque<T>>
class stack {
    friend bool operator == (const stack&, const stack&);
    friend bool operator < (const stack&, const stack&);

public:
    typedef typename Sequence::value_type value_type;
    typedef typename Sequence::size_type size_type;
    typedef typename Sequence::reference reference;
    typedef typename Sequence::const_reference const_reference;

protected:
    Sequence c;     //µ×²ãÈÝÆ÷
public:
    bool empty() { return c.empty(); }
    size_type size() { return c.size(); }
    reference top() { return c.back(); }
    const_reference top() { return c.back(); }
    void push(const value_type& x) { c.push_back(x); }
    void pop() { c.pop_back(); }
};

template <class T, class Sequence>
bool operator == (const stack<T, Sequence>& x, const stack<T, Squence>& y) {
    return x.c == y.c;
}

template <class T, class Sequence>
bool operator < (const stack<T, Sequence>& x, const stack<T, Squence>& y) {
    return x.c < y.c;
}

#endif // STACK_H_INCLUDED
