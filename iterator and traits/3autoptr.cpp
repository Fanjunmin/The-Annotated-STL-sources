//3.2 简化版本的auto_ptr，说明auto_ptr的行为和能力
//filename : 3autoptr.cpp

template <typename T>
class auto_ptr {
public:
    explicit auto_ptr(T *p = 0) : pointee(p) {} //抑制构造函数隐式转换
    template<typename U>
    auto_ptr(auto_ptr<U>& rhs) : pointee(rhs.release()) {}  //使用一个类型兼容的auto进行构造
    ~auto_ptr() {delete pointee;}

    template<typename U>
    auto_ptr<T>& operator=(auto_ptr<U>& rhs) {
        if(this != &rhs) reset(rhs.release());
        return *this;
    }
    T& operator*() const {return *pointee;}
    T* operator->() const {return pointee;}
    T* get() const {return pointee;}
    T* release(){   //放弃所有权
        T* oldpointee(pointee);
        pointee = 0;
        return oldpointee;
    }
    void reset(T *p = 0){
        if(pointee != p){
            delete pointee;
            pointee = p;
        }
    }

private:
    T *pointee;
};

#include "iostream"
#include <string>
using namespace std;

int main(){
    auto_ptr<string> sa(new string("sas"));
    cout << *sa.get() << endl;
    string s = "asdsadsa";
    sa.reset(&s);
    cout << *sa.get() << endl;
    return 0;
}
