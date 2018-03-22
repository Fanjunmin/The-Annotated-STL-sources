//4.8.1 优先队列
//filename:priority_queue
#ifndef PRIORITY_QUEUE_H_INCLUDED
#define PRIORITY_QUEUE_H_INCLUDED

template <class T, class Sequence = vector<T>,
        class Compare = less<typename Sequence::value_type>>
class priority_queue
{
public:
    typedef typename Sequence::value_type value_type;
    typedef typename Sequence::size_type size_type;
    typedef typename Sequence::reference reference;
    typedef typename Sequence::const_reference const_reference;
protected:
    Sequence c;
    Compare comp;
public:
    priority_queue() : c() { }
    explicit priority_queue(Compare x) : c(), comp(x) { }
    template <class InputIterator>
    priority_queue(InputIterator first, InputIterator last, const Compare& x)
            : c(first, last), comp(x) { }
    template <class InputIterator>
    priority_queue(InputIterator first, InputIterator last)
            : c(first, last) { make_heap(first, last); }
    bool empty() { return c.empty(); }
    size_type size() { return c.size(); }
    reference top() { return c.front(); }
    const_reference top() { return c.front(); }
    void push(const value_type& x) { c.push_back(x); push_heap(c.begin(), c.end()); }
    void pop() { c.pop_heap(); pop_back(x); }
};


#endif // PRIORITY_QUEUE_H_INCLUDED
