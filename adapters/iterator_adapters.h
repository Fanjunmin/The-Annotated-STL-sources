#ifndef ITERATOR_ADAPTERS_H_INCLUDED
#define ITERATOR_ADAPTERS_H_INCLUDED

template<class Container>
class my_back_insert_iterator {
protected:
    Container* container;   //µ×²ãÈÝÆ÷

public:
    typedef output_iterator_tag iterator_category;
    typedef void                value_type;
    typedef void                difference_type;
    typedef void                pointer;
    typedef void                reference;
    explicit my_back_insert_iterator(Container& x) : container(x) { }
    my_back_insert_iterator<container>& operator= (const typename Container::value_type& value) {
        container->push_back(value);
        return *this;
    }
    my_back_insert_iterator<container>& operator*() { return *this; }
    my_back_insert_iterator<container>& operator++() { return *this; }
    my_back_insert_iterator<container>& operator++(int) { return *this; }

    template<class Container>
    inline my_back_insert_iterator<Container> back_inserter(Container& x){
        return my_back_insert_iterator<container>(x);
    }
};

template<class Container>
class my_front_insert_iterator {
protected:
    Container* container;   //µ×²ãÈÝÆ÷

public:
    typedef output_iterator_tag iterator_category;
    typedef void                value_type;
    typedef void                difference_type;
    typedef void                pointer;
    typedef void                reference;
    explicit my_front_insert_iterator(Container& x) : container(x) { }
    my_front_insert_iterator<container>& operator= (const typename Container::value_type& value) {
        container->push_front(value);
        return *this;
    }
    my_front_insert_iterator<container>& operator*() { return *this; }
    my_front_insert_iterator<container>& operator++() { return *this; }
    my_front_insert_iterator<container>& operator++(int) { return *this; }

    template<class Container>
    inline my_front_insert_iterator<Container> back_inserter(Container& x){
        return my_front_insert_iterator<container>(x);
    }
};

template<class Container>
class my_insert_iterator {
protected:
    Container* container;   //µ×²ãÈÝÆ÷
    typename Container::iterator iter;
public:
    typedef output_iterator_tag iterator_category;
    typedef void                value_type;
    typedef void                difference_type;
    typedef void                pointer;
    typedef void                reference;
    explicit my_insert_iterator(Container& x, typename Container::iterator i) : container(x), iter(i) { }
    my_insert_iterator<container>& operator= (const typename Container::value_type& value) {
        container->insert(iter, value);
        ++iter;
        return *this;
    }
    my_insert_iterator<container>& operator*() { return *this; }
    my_insert_iterator<container>& operator++() { return *this; }
    my_insert_iterator<container>& operator++(int) { return *this; }

    template<class Container, class Iterator>
    inline my_insert_iterator<Container> inserter(Container& x, Iterator i){
        typename typename Container::iterator iter;
        return my_insert_iterator<container>(x, iter(i));
    }
};

#endif // ITERATOR_ADAPTERS_H_INCLUDED
