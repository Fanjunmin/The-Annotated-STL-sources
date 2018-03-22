//4.6.2
//filename:queue.h
#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED
template <class T, class Sequence = deque<T>>
class queue
{
    friend bool operator == (const stack&, const stack&);
    friend bool operator < (const stack&, const stack&);
public:
    typedef typename Sequence::value_type value_type;
    typedef typename Sequence::size_type size_type;
    typedef typename Sequence::reference reference;
    typedef typename Sequence::const_reference const_reference;
protected:
    Sequence c;
public:
    bool empty() { return c.empty(); }
    size_type size() { return c.size(); }
    reference front() { return c.front(); }
    reference back() { return c.back(); }
    const_reference front() { return c.front(); }
    const_reference back() { return c.back(); }
    void push(const value_type& x) { c.push_back(x); }
    void pop() { c.pop_front(); }
};

template <class T, class Sequence>
bool operator == (const queue<T, Sequence>& x, const queue<T, Squence>& y) {
    return x.c == y.c;
}

template <class T, class Sequence>
bool operator < (const queue<T, Sequence>& x, const queue<T, Squence>& y) {
    return x.c < y.c;


#endif // QUEUE_H_INCLUDED
