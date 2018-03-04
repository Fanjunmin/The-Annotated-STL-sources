//3.2 为链表list涉及一个迭代器，下面是list及其节点的结构
//filename : 3mylist.h

template <typename T>
class ListItem{
public:
    T value() const {return _value;}
    ListItem* next() const {return *_next;}

private:
    T _value;
    ListItem *_next;    //单向链表
};

template <typename T>
class List{
public:
    void insert_front(T value){
        _front->_value = value;
    }
    void insert_end(T value){
        _end->_value = value;
    }
    void display(std::ostream &os = std::cout) const{
        while(_front++ != _end)
            os << _front->value() << std::ends;
        os << _end->value() << std::endl;
    }

private:
    ListItem<T> *_end;
    ListItem<T> *_front;
    long _size;
};
